# TODO — Codebase Audit Findings

Full audit of `include/simo/**` (2026-07-05). Items are ordered by priority: performance issues first (performance is critical for this library), then correctness bugs, then robustness/hygiene. Line numbers refer to the multi-header sources under `include/`; remember the fixes must be re-amalgamated into `single_include/` (see last item).

## 🔥 Performance — Critical

- [x] **Remove debug `std::cout` from `geometry_t` special members** (`include/simo/geom/geometry.hpp:73,79,249,259` and every case of the destructor at `:424+`)
  **Problem:** Every default-construct, copy, move, assignment, and destruction of `geometry_t` prints `"DEFAULT CONSTRUCTOR"`, `"COPY ASSIGNMENT"`, `"DELETE POINT"`, etc. to stdout. This makes the type-erased API orders of magnitude slower (I/O + flush via `std::endl` per object) and pollutes the stdout of every consuming application. These statements are shipped in the released `single_include/simo/shapes.hpp`.
  **Fix:** Delete all `std::cout` lines and drop the now-unneeded `<iostream>` dependency from the hot path.
  ```cpp
  // before
  geometry_t() { std::cout << "DEFAULT CONSTRUCTOR" << std::endl; }
  // after
  geometry_t() = default;   // union already value-initialized via `geom_value m_value = {};`
  ```

- [x] **Add the missing move-assignment operator to `geometry_t`** (`include/simo/geom/geometry.hpp:247`)
  **Problem:** A user-declared copy-assignment suppresses the implicit move-assignment, so `g = std::move(other)` silently performs a full deep copy (heap allocation + element-wise copy of the entire geometry).
  **Fix:** Add a swap-based move assignment next to the existing copy assignment:
  ```cpp
  geometry_t& operator=(geometry_t&& other) noexcept
  {
      swap(*this, other);
      return *this;
  }
  ```

- [x] **Stop parsing WKT twice in `geometry_t::from_wkt_`** (`include/simo/geom/geometry.hpp:1615-1681`)
  **Problem:** The method runs a full `wkt_reader::read(wkt)` just to learn the geometry type, then calls e.g. `linestring_t<T>::from_wkt(wkt)` which constructs a *second* lemon parser (`ParseAlloc`/`ParseFree`) and lexes/parses the entire string again. Every `from_wkt` call costs 2× parse + 2 parser allocations.
  **Fix:** Build the concrete geometry directly from the first parse's `wkt_result` (the coords/offsets are already in `result.data`):
  ```cpp
  auto result = reader.read(wkt);
  switch (result.data.geom_type) {
      case geometry_type::LINESTRING:
          return geometry_t<T>(linestring_t<T>(result.data.coords.begin(),
                                               result.data.coords.end()));
      // ... build each type from result.data instead of re-parsing `wkt`
  }
  ```

- [x] **Eliminate mandatory heap allocation per `geometry_t` + 64 bytes of dead `shared_ptr` weight** (`include/simo/geom/geometry.hpp:1238-1406`)
  **Problem:** (a) Every payload — even a 16-byte point — is stored as `new T(copy)` behind the `geom_value` union of pointers, so constructing/copying any `geometry_t` always heap-allocates. (b) Geometry collections are stored in four *always-present* `std::shared_ptr` members outside the union (`m_geometrycollection[_z|_m|_zm]`), adding ~64 bytes to every `geometry_t` instance and shared_ptr control-block allocations, while their sharing semantics are unused (copies are deep anyway).
  **Fix:** Store small types (all four point variants) inline in the union; keep heap storage only for containers, and fold the collection pointers into the union as raw owned pointers handled by the existing destructor switch:
  ```cpp
  union geom_value {
      point_t<T>    m_point;        // inline, no allocation
      point_z_t<T>  m_point_z;      // ...
      linestring_t<T>*          m_linestring;         // heap only for containers
      geometrycollection_t<T>*  m_geometrycollection; // moved into the union
      // ...
  };
  // sizeof(geometry_t) drops from ~80 bytes to ~40, and point wrapping is allocation-free
  ```

- [x] **WKB reader: remove double buffer copy and per-child `geometry_t` round-trip** (`include/simo/io/wkb_reader.hpp:24,186-202,298-307`)
  **Problem:** (1) `read_wkb(first, last)` copies the input byte-by-byte with `push_back` and no `reserve`; (2) `wkb_reader` stores `bytes_` by value, copying the buffer a second time; (3) `read_geometry_children` parses each child into a full `geometry_t` (heap allocation, see above), then `*child.get<ChildType>()` copies it *again* into the container, then destroys the temporary. Reading a MultiPoint of N points costs ~3N allocations and 2 full buffer copies.
  **Fix:** Parse from a raw span and read children as their concrete type:
  ```cpp
  wkb_reader(const std::uint8_t* data, std::size_t size);      // no owning copy

  template <typename ChildType>
  ChildType read_typed_child(bool /*outer*/)                   // header + payload,
  {                                                            // no geometry_t wrapper
      const auto order = read_u8();
      const bool le    = order == 1;
      const auto type  = decode_type(read_u32(le));
      if (type != expected_type_of<ChildType>()) throw exceptions::parse_error(...);
      return read_payload<ChildType>(le);
  }
  ```

- [x] **Fix 2–4× over-reservation in coordinate-iterator constructors** (`include/simo/geom/detail/linestring.hpp:43,54`, `polygon.hpp:53,64`, `multipoint.hpp:40,51`)
  **Problem:** `this->reserve(std::distance(first, last))` reserves one slot per *coordinate*, but the loop emplaces one element per *point* (`ndim` coordinates). A 3D linestring reserves 3× the memory it needs; it's never shrunk.
  **Fix:**
  ```cpp
  size_t n = this->ndim();
  this->reserve(static_cast<size_t>(std::distance(first, last)) / n);
  ```

- [x] **Replace per-geometry `stringstream` + per-child string temporaries in all serializers** (`wkt_`/`json_` in `point.hpp`, `linestring.hpp`, `polygon.hpp`, `multi*.hpp`, `geometry.hpp:2037-2106`)
  **Problem:** Every geometry builds its own `std::stringstream` (locale-aware, allocation-heavy) and returns a `std::string`; parents stream those strings into *their own* stringstream. Serializing a collection of N children costs N stringstreams + N intermediate strings + N re-copies. Stream `operator<<` for doubles is also one of the slowest formatting paths available.
  **Fix:** One growing buffer threaded through the hierarchy, plus a fast double formatter:
  ```cpp
  void write_wkt(std::string& out, std::int32_t precision) const;  // children append in place

  inline void append_double(std::string& out, double v, int precision)
  {
      char buf[32];
      int len = std::snprintf(buf, sizeof(buf), "%.*g", precision, v); // or to_chars (C++17)
      out.append(buf, static_cast<size_t>(len));
  }
  ```

- [x] **GeoJSON `parse_number` allocates a `std::string` per number** (`include/simo/io/geojson_parser.hpp:347-348`)
  **Problem:** After scanning the number's extent, the parser does `std::string num_str(start, pos_); return std::stod(num_str);` — one heap allocation and one copy *per coordinate*. Parsing a large FeatureCollection allocates millions of throwaway strings.
  **Fix:** Convert in place from the existing buffer (also removes one locale hazard — see the `stod` item below):
  ```cpp
  char* parse_end = nullptr;
  double value = std::strtod(start, &parse_end);   // pos_ already validated the extent
  pos_ = parse_end;
  return value;
  ```

- [x] **`wkt_reader::normalize_result` re-scans and copies the whole WKT input** (`include/simo/io/wkt_reader.hpp:99-179`; same pattern in `geometry.hpp:2499-2512`)
  **Problem:** After a successful parse, `normalize_result` calls `compact_upper(wkt)` — a full copy + uppercase of the entire input — just to check for `"EMPTY"`, and `multipolygon_polygon_offsets` re-walks the raw text counting parens because the lemon parser doesn't emit polygon offsets. `geometry_t::is_geometrycollection_wkt_` does the same full copy merely to test a prefix. Every parse pays 2–3 extra O(n) passes and allocations.
  **Fix:** Emit `polygon_offsets` and an `is_empty` flag from the grammar actions in `wkt_parser.y`, and test prefixes in place:
  ```cpp
  static bool starts_with_geometrycollection(const std::string& wkt)
  {
      size_t i = wkt.find_first_not_of(" \t\r\n");
      const char* kw = "GEOMETRYCOLLECTION";
      for (size_t k = 0; kw[k]; ++k, ++i)
          if (i >= wkt.size() || std::toupper((unsigned char)wkt[i]) != kw[k]) return false;
      return true;
  }
  ```

- [x] **`convex_hull` comparator calls `sqrt` for every comparison** (`include/simo/algorithm/operations.hpp:65`)
  **Problem:** The polar-angle sort's collinear tie-break uses `distance()` (which calls `std::sqrt`) inside the `std::sort` comparator — O(n log n) square roots for a pure ordering decision.
  **Fix:** Compare squared distances (monotonic, exact for the comparison):
  ```cpp
  auto sq = [](const Point& a, const Point& b) {
      auto dx = b.x - a.x, dy = b.y - a.y;
      return dx * dx + dy * dy;
  };
  if (o == 0) return sq(pivot, a) < sq(pivot, b);
  ```

- [x] **`wkb_writer::bytes()` copies the output buffer; writer never reserves** (`include/simo/io/wkb_writer.hpp:328-331,509-515`)
  **Problem:** `write_wkb` finishes with `return writer.bytes();` which returns `bytes_` *by value copy* (the member outlives the call). The buffer also grows with per-byte `push_back` with no initial `reserve`.
  **Fix:**
  ```cpp
  std::vector<std::uint8_t> take() { return std::move(bytes_); }
  // in write_wkb:
  writer.reserve_hint(geometry);   // e.g. 9 + point_count * 8 * ndim
  writer.write_geometry(geometry);
  return writer.take();
  ```

- [x] **`geometry_t::get<T>()` is a runtime chain of 28 compile-time-known checks** (`include/simo/geom/geometry.hpp:612-749`)
  **Problem:** All 28 `is_basic_*<ReturnType>::value` conditions are constants for a given instantiation, yet compile as a sequential if-chain; the dead branches also force `reinterpret_cast` through unrelated getters (and inhibit inlining).
  **Fix (C++14):** tag-dispatch so each instantiation compiles to a single member access:
  ```cpp
  template <typename R>
  R* get() { return get_impl(static_cast<R*>(nullptr)); }

private:
  point_t<T>*      get_impl(point_t<T>*)      { return get_point(); }
  linestring_t<T>* get_impl(linestring_t<T>*) { return get_linestring(); }
  // ... one overload per supported type; anything else fails to compile instead of returning nullptr
  ```

## 🐛 Correctness Bugs

- [x] **`bounds_t` initializes `maxx`/`maxy` with `numeric_limits<double>::min()`** (`include/simo/geom/detail/bounds.hpp:41-42`)
  **Problem:** `min()` for floating point is the smallest *positive normal* (~2.2e-308), not the most negative value. Any geometry whose x (or y) coordinates are all negative gets `maxx ≈ 2.2e-308` because `std::max(x, 2.2e-308)` never picks a negative `x`. All bounds/envelope/bbox-predicate results are wrong in the negative quadrants.
  **Fix:**
  ```cpp
  bounds_t()
      : minx(std::numeric_limits<double>::max()),
        miny(std::numeric_limits<double>::max()),
        maxx(std::numeric_limits<double>::lowest()),   // was ::min()
        maxy(std::numeric_limits<double>::lowest())
  {}
  ```

- [x] **`*this[0]` — indexing the `this` pointer instead of the container** (`include/simo/geom/detail/linestring.hpp:212`, `multipoint.hpp:173`, `multilinestring.hpp:127`)
  **Problem:** `*this[0] == *this[1]` parses as `*(this[1])` — array arithmetic on the `this` pointer, i.e. dereferencing "the object after this one" in memory. These template members currently fail to even compile when instantiated (no test calls `linestring::throw_for_invalid_()`, `multipoint::is_closed_()`, or `multilinestring::is_closed_()`), so the API is broken the moment a user touches it.
  **Fix:**
  ```cpp
  // linestring::throw_for_invalid_
  if ((*this)[0] == (*this)[1]) { ... }
  // multipoint/multilinestring::is_closed_
  return (*this)[0] == (*this)[this->size() - 1];
  ```
  Add tests that call `is_valid()`/`is_closed()` on all three types so the members are instantiated.

- [x] **`rotate`/`scale` produce points flagged as EMPTY** (`include/simo/algorithm/transformations.hpp:135-139,186-189`; same pattern in `predicates.hpp:198-200`)
  **Problem:** `Point result;` uses the default constructor which sets `m_empty = true`; assigning `.x`/`.y` afterwards never clears it. Rotated/scaled points report `empty() == true`, `size() == 0`, serialize as `POINT EMPTY`, and iterate zero coordinates. Existing tests pass only because `operator==` short-circuits to `true` when *both* operands claim to be empty.
  **Fix:** Construct through the value constructor:
  ```cpp
  return Point{origin.x + dx * cos_a - dy * sin_a,
               origin.y + dx * sin_a + dy * cos_a};
  ```

- [x] **Default serialization truncates coordinates to 6 significant digits** (all `wkt_`/`json_` methods, e.g. `include/simo/geom/detail/point.hpp:346-361`)
  **Problem:** With the default `precision = -1` nothing calls `setprecision`, so streams use the default 6 significant digits: `point(-122.4194155, 37.7749295).wkt()` → `"POINT (-122.419 37.7749)"`. Round-tripping through WKT/GeoJSON silently loses data. (Also note `std::setprecision` means *significant digits*, not decimal places — worth documenting.)
  **Fix:**
  ```cpp
  ss << std::setprecision(precision >= 0
         ? precision
         : std::numeric_limits<T>::max_digits10);   // 17 for double → lossless round-trip
  ```

- [x] **`geometry_t` facade returns hardcoded constants for `bounds`/`dim`/`has_z`/`has_m`/`is_closed`** (`include/simo/geom/geometry.hpp:1420-1460`)
  **Problem:** The type-erased wrapper implements `dim_()` → always `XY`, `ndim_()` → always `2`, `has_z_()`/`has_m_()` → always `true`, `is_closed_()` → always `true`, and `bounds_()` → `{}` (an *inverted* empty box). So `from_wkt("POINT Z (1 2 3)").dim()` reports XY and `.bounds()` is garbage — only `json()`/`wkt()` dispatch correctly.
  **Fix:** Dispatch on `m_geom_type` exactly like `json_`/`wkt_` do:
  ```cpp
  bounds_t bounds_() const
  {
      switch (m_geom_type) {
          case geometry_type::POINT:      return m_value.m_point->bounds();
          case geometry_type::LINESTRING: return m_value.m_linestring->bounds();
          // ... all cases, incl. collections
      }
  }
  // same treatment for dim_/ndim_/has_z_/has_m_/is_closed_
  ```

- [x] **`size_t` underflow loops on empty inputs in predicates** (`include/simo/algorithm/predicates.hpp:75-77`, `include/simo/algorithm/detail/point_in_polygon.hpp:31,74`)
  **Problem:** `for (size_t i = 0; i < ls.size() - 1; ++i)` with `size() == 0` computes `SIZE_MAX` and reads far out of bounds. Reachable: `intersects()`'s bbox pre-check does not reliably reject empty linestrings (an empty bounds_t can still "intersect" boxes spanning tiny positive values), and `winding_number`/`point_on_boundary` receive rings straight from user polygons which may be empty.
  **Fix:** Underflow-safe loop bounds plus early exits:
  ```cpp
  if (ls1.size() < 2 || ls2.size() < 2) return false;     // intersects
  for (size_t i = 0; i + 1 < ring.size(); ++i) { ... }    // winding_number / point_on_boundary
  ```

- [x] **`convex_hull` sort comparator violates strict weak ordering** (`include/simo/algorithm/operations.hpp:56-68`)
  **Problem:** `if (a == pivot) return true;` fires even when `b == pivot` as well, so `comp(x, x) == true` for pivot duplicates — undefined behavior in `std::sort` (real-world consequence: crashes/infinite loops on inputs containing the pivot point more than once).
  **Fix:**
  ```cpp
  bool a_is_pivot = (a.x == pivot.x && a.y == pivot.y);
  bool b_is_pivot = (b.x == pivot.x && b.y == pivot.y);
  if (a_is_pivot || b_is_pivot) return a_is_pivot && !b_is_pivot;
  ```

- [x] **ODR violations: non-`inline` free functions defined in headers** (`include/simo/geom/detail/utils.hpp` — all 8 functions; `include/simo/io/polyline.hpp` — `encode`, `advance`, `decode`)
  **Problem:** These are non-template, non-inline function *definitions* in headers of a header-only library. Any project including shapes from two translation units gets duplicate-symbol link errors.
  **Fix:**
  ```cpp
  inline dimension_type get_dim(geometry_type geom_type) noexcept { ... }
  inline std::string encode(double coord, int32_t precision = 5) { ... }
  // mark every free function in both files `inline`
  ```

- [x] **Polyline `encode`: UB on negative left-shift + wrong sign source + missing includes** (`include/simo/io/polyline.hpp:33-52`)
  **Problem:** (1) `value <<= 1` where `value` is a negative `int32_t` is undefined behavior before C++20. (2) The sign test uses the *raw* `coord < 0` instead of the rounded integer: `coord = -1e-9` rounds to `0` but still takes the `~value` branch, encoding delta −1 instead of 0. (3) The header uses `std::pow`, `std::round`, `assert`, `std::string`, `std::vector` without including `<cmath>`, `<cassert>`, `<string>`, `<vector>`, `<cstdint>`.
  **Fix:** Follow the reference algorithm in unsigned arithmetic:
  ```cpp
  auto v  = static_cast<std::int32_t>(std::round(coord * pow10));
  auto uv = static_cast<std::uint32_t>(v) << 1;
  if (v < 0) uv = ~uv;
  while (uv >= 0x20) { out += char((uv & 0x1f) | 0x20) + 63; uv >>= 5; }
  out += char(uv + 63);
  ```

- [x] **`basic_point::from_polyline` reads out of bounds on short input** (`include/simo/geom/detail/point.hpp:162-170`)
  **Problem:** Only `coords.size() > N` is rejected; an empty or truncated polyline string yields fewer than 2 decoded values and `coords[0]`/`coords[1]` read past the end of an empty vector.
  **Fix:**
  ```cpp
  auto coords = polyline::decode(polyline, precision);
  if (coords.size() != N) throw exceptions::parse_error("invalid polyline point");
  return {coords[0], coords[1]};
  ```

- [x] **Locale-dependent number parsing via `std::stod`** (`include/simo/io/wkt_reader.hpp:76`, `include/simo/io/geojson_parser.hpp:348`)
  **Problem:** `std::stod` honors the global `LC_NUMERIC`. In a process running under e.g. `de_DE` (comma decimal separator), `"1.5"` parses as `1.0` — silent coordinate corruption for every WKT/GeoJSON read.
  **Fix:** Locale-independent conversion — `std::from_chars` (if bumping to C++17), or a small hand-rolled decimal parser / `strtod_l` with the C locale:
  ```cpp
  double value{};
  auto [ptr, ec] = std::from_chars(first, last, value);   // C++17; never locale-dependent
  if (ec != std::errc{}) throw exceptions::parse_error("invalid number");
  ```

- [x] **GeoJSON parser: unbounded recursion → stack overflow on hostile input** (`include/simo/io/geojson_parser.hpp:352-516`)
  **Problem:** `parse_value` → `parse_array`/`parse_object` recurse once per nesting level with no limit; a few KB of `[[[[[…` crashes the process. Same consideration applies to `wkb_reader::read_geometry` with deeply nested GEOMETRYCOLLECTIONs.
  **Fix:**
  ```cpp
  static constexpr int MAX_DEPTH = 512;
  int depth_ = 0;
  geojson_value parse_value()
  {
      if (++depth_ > MAX_DEPTH) throw geojson_parse_error("nesting too deep");
      ...
      --depth_;
  }
  ```

- [x] **GeoJSON parser rejects valid `\uXXXX` escapes** (`include/simo/io/geojson_parser.hpp:279-281`)
  **Problem:** The escape switch throws `"invalid escape sequence"` for `\u`, so any spec-conformant document with a unicode escape in a property/name string fails to parse.
  **Fix:** Decode the 4 hex digits (and surrogate pairs) to UTF-8:
  ```cpp
  case 'u': {
      unsigned cp = parse_hex4();
      if (cp >= 0xD800 && cp <= 0xDBFF) cp = combine_surrogate(cp, parse_next_hex4());
      append_utf8(result, cp);
      break;
  }
  ```

- [x] **`point_on_boundary`'s `tolerance` parameter is accepted, documented, and ignored** (`include/simo/algorithm/detail/point_in_polygon.hpp:72`)
  **Problem:** Callers passing a tolerance get exact `orient2d == 0` matching regardless — near-boundary points are never reported as touching.
  **Fix:** Either implement it (compare squared point-to-segment distance against `tolerance²`) or remove the parameter so the signature stops lying:
  ```cpp
  if (squared_segment_distance(v1, v2, point) <= tolerance * tolerance) return true;
  ```

- [x] **`orient2d` documents "exact arithmetic … robustness" but is plain floating point** *(comment + includes fixed; robust predicate not implemented)* (`include/simo/algorithm/detail/orient2d.hpp:28-41`; also missing `<algorithm>`/`<cmath>` for `std::max`/`std::min` used in `on_segment`)
  **Problem:** The naive cross product misclassifies nearly collinear inputs (rounding), which propagates into convex hull, point-in-polygon and segment intersection producing wrong answers on real-world data. The doc comment overpromises. `on_segment` also relies on transitive includes for `std::max/min`.
  **Fix:** Add `#include <algorithm>`; correct the comment; optionally upgrade to a robust predicate:
  ```cpp
  // Fast path + error-bound filter (Shewchuk-style); fall back to exact evaluation when
  // |det| is below the rounding-error bound for the input magnitudes.
  ```

- [x] **`centroid` divides by zero for degenerate polygons** (`include/simo/algorithm/operations.hpp:273-275`)
  **Problem:** A zero-area ring (all points collinear or repeated) gives `signed_area == 0`, producing NaN/±inf coordinates with no diagnostic.
  **Fix:**
  ```cpp
  if (signed_area == 0)
  {   // degenerate: fall back to vertex average
      return vertex_mean(ring);
  }
  ```

- [x] **`overlaps()` is only a bounding-box test but carries an OGC predicate name** *(resolved by renaming to `bounds_overlap`)* (`include/simo/algorithm/predicates.hpp:219-227`)
  **Problem:** `overlaps(g1, g2)` returns `bounds_intersect(...)` — two disjoint concave shapes with intersecting boxes report `true`. Users relying on OGC semantics get wrong answers with no warning beyond a code comment.
  **Fix:** Rename to `bounds_overlap` (and keep `overlaps` unimplemented/`= delete`d until real support exists), or implement the actual predicate on top of `intersects` + `within`.

- [x] **`wkt_reader` is copyable with a raw owning pointer → double `ParseFree`** (`include/simo/io/wkt_reader.hpp:30-39,182`)
  **Problem:** Rule-of-three violation: the compiler-generated copy duplicates `m_parser`, and both destructors call `ParseFree` on the same allocation (heap corruption).
  **Fix:**
  ```cpp
  wkt_reader(const wkt_reader&) = delete;
  wkt_reader& operator=(const wkt_reader&) = delete;
  wkt_reader(wkt_reader&& o) noexcept : m_parser(o.m_parser) { o.m_parser = nullptr; }
  ```

- [x] **WKB reader trusts attacker-controlled counts for `reserve`** (`include/simo/io/wkb_reader.hpp:163,178,191,209`)
  **Problem:** `count` is a raw `uint32` from the wire; a 9-byte crafted buffer declaring 4 billion points triggers a multi-GB `reserve` (OOM / allocation-failure DoS) before any bounds check runs.
  **Fix:** Validate the count against remaining input before reserving:
  ```cpp
  const auto count = read_u32(little_endian);
  require(static_cast<std::size_t>(count) * MIN_CHILD_BYTES);  // e.g. 16 for a 2D point
  points.reserve(count);
  ```

- [x] **`geometry_t` getters are unchecked in release builds → type-confusion UB** (`include/simo/geom/geometry.hpp:907+`, `get<T>()` at `:612`)
  **Problem:** `get_point()` et al. only `assert` the tag; with `NDEBUG` a mismatched call returns the wrong union member reinterpret-casted to the requested type — silent memory corruption instead of an error.
  **Fix:** Check the tag unconditionally:
  ```cpp
  point_t<T>* get_point() noexcept
  {
      return m_geom_type == geometry_type::POINT ? m_value.m_point : nullptr;
  }
  ```

## 🧹 Robustness & Hygiene

- [x] **Missing `const` qualifiers** — all 28 `geometry_t::is_*()` predicates (`geometry.hpp:753-903`), `bounds_t::contains(bounds_t)/intersects/overlaps` (`bounds.hpp:165-190`), and `basic_point::operator[]` lacks a const overload. None are callable on `const` objects.
  ```cpp
  inline bool is_point() const { return m_geom_type == geometry_type::POINT; }
  bool intersects(const bounds_t& other) const { ... }
  const_reference operator[](size_t pos) const { assert(pos < N); return coords[pos]; }
  ```

- [x] **Douglas-Peucker recursion is O(n) deep in the worst case** (`include/simo/algorithm/operations.hpp:142-181`)
  **Problem:** Adversarial/monotone inputs recurse once per point — stack overflow on large linestrings.
  **Fix:** Iterative version with an explicit work stack:
  ```cpp
  std::vector<std::pair<size_t, size_t>> stack{{0, points.size() - 1}};
  while (!stack.empty()) { auto [start, end] = stack.back(); stack.pop_back(); ... }
  ```

- [x] **Duplicated WKT-collection helpers** — `parse_collection_type` (`geometry.hpp:1869`) and `geometrycollection_type_from_wkt_` (`geometry.hpp:2515`) are identical copy-pastes; `compact_upper`/`trim` are defined three times (`geometry.hpp`, `wkt_reader.hpp`). Consolidate into one `detail::wkt_util` header so fixes (like the prefix-scan performance item) land once.

- [ ] **Public inheritance from `std::vector`** *(deferred: larger API-surface refactor, tracked separately)* (`basic_linestring`, `basic_polygon`, `basic_multipoint`, `basic_multilinestring`, `basic_multipolygon`, `basic_geometrycollection`)
  **Problem:** `std::vector` has no virtual destructor; deleting a geometry through a `std::vector*` is UB, and the entire mutable vector API (e.g. `resize` on a polygon's ring list) bypasses geometry invariants.
  **Fix (larger refactor, low urgency):** private inheritance or composition + `using base_type::begin; using base_type::end; ...` for the intended surface.

- [x] **Regenerate `single_include/simo/shapes.hpp` after applying fixes**
  **Problem:** The released single header currently ships the debug `cout`s and every bug above (verified: 5 debug-print markers present).
  **Fix:** After the source fixes, run the amalgamation target and commit the result:
  ```bash
  cmake --build build --target shapes_amalgamate
  ```
