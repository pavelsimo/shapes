# shapes
[![Build Status](https://travis-ci.org/pavelsimo/shapes.svg?branch=master)](https://travis-ci.org/pavelsimo/shapes)
[![Build Status](https://ci.appveyor.com/api/projects/status/nhl73vfksg69jbx2?svg=true)](https://ci.appveyor.com/project/pavelsimo/shapes)
[![codecov](https://codecov.io/gh/pavelsimo/shapes/branch/master/graph/badge.svg)](https://codecov.io/gh/pavelsimo/shapes)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://pavelsimo.github.io/shapes)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/022c774e43264ec4a04c4ccdeda9ae27)](https://www.codacy.com/app/pavelsimo/shapes?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pavelsimo/shapes&amp;utm_campaign=Badge_Grade)
[![](https://img.shields.io/github/license/pavelsimo/shapes.svg)](https://github.com/pavelsimo/shapes/blob/master/LICENSE)

A lightweight header-only geometry library for Modern C++14

- Inspired by python [shapely](https://pypi.org/project/Shapely/)
- Based on OGC [Simple Features](https://en.wikipedia.org/wiki/Simple_Features)
- Built on top of STL containers
- **Zero external dependencies** (header-only)
- Comprehensive geometric algorithms (measurements, predicates, operations, transformations)

## Installation

`shapes` ships as a header-only library:

```cpp
#include <simo/shapes.hpp>

using namespace simo::shapes;
```

## Examples

Building a `Point` from GeoJSON:

```cpp
auto p = Point::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0]})");
std::cout << p.x << " " << p.y << " " << '\n';
```

GeoJSON representation of a 3d `Point`:

```cpp
auto p = PointZ{1, 2, 3};
std::cout << p.json() << '\n';
```

```json
{"coordinates":[1.0,2.0,3.0],"type":"Point"}
``` 

Iterating a `MultiPoint` is as simple as:

```cpp
auto mp = MultiPoint{{0, 0}, {1, 2}, {4, 5}, {7, 7}};
for(const auto& p: mp)
{
    std::cout << p.x << " " << p.y << '\n';
} 
```

WKT representation of a `MultiPoint`:

```cpp
auto mp = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
std::cout << mp.wkt() << '\n';
```

```text
MULTIPOINTZ((1.0 2.0 3.0),(4.0 5.0 6.0))
```

Creating a `LineString` from a google polyline:

```cpp
std::string polyline = "_p~iF~ps|U_ulLnnqC_mqNvxq`@";
auto ls = LineString::from_polyline(polyline);
std::cout << points.wkt() << '\n';
```

```text
LINESTRING(-120.2 38.5,-120.95 40.7,-126.453 43.252)
```

Google Polyline representation of a `LineString`:

```cpp
auto ls = LineString{{-120.2, 38.5}, {-120.95, 40.7}, {-126.453, 43.252}};
std::cout << ls.polyline() << '\n';
```

```text
_p~iF~ps|U_ulLnnqC_mqNvxq`@
```

Building a `MultiLineString`:

```cpp
auto ml = MultiLineString{
    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}
};
```

Applying a basic transformation to a `MultiPoint`:

```cpp
auto mp  = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
std::transform(mp.begin(), mp.end(), mp.begin(), [](const Point& p) -> Point {
  return {p.x + 10, p.y + 10};
});
std::cout << mp.wkt() << '\n';
```

```text
MULTIPOINT((11 12),(13 14))
```

## Geometric Algorithms

The library provides comprehensive geometric algorithms inspired by Shapely:

### Measurements

Calculate geometric properties:

```cpp
using namespace simo::shapes;
using namespace simo::shapes::algorithm;

// Area of a polygon
Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
auto a = area(square);  // 16.0

// Or use the method:
auto a2 = square.area();  // 16.0

// Length of a linestring
LineString path{{0, 0}, {3, 0}, {3, 4}};
auto len = path.length();  // 7.0

// Distance between points
Point p1{0, 0};
Point p2{3, 4};
auto dist = distance(p1, p2);  // 5.0
```

### Binary Predicates

Test spatial relationships:

```cpp
// Point in polygon
Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
Point inside{2, 2};
Point outside{5, 5};

bool result1 = contains(square, inside);   // true
bool result2 = square.contains(outside);   // false

// Intersection test
LineString ls1{{0, 0}, {4, 4}};
LineString ls2{{0, 4}, {4, 0}};
bool crosses = intersects(ls1, ls2);  // true

// Within test
bool is_within = within(inside, square);  // true
```

### Constructive Operations

Create new geometries from existing ones:

```cpp
// Convex hull
MultiPoint points{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}};
auto hull = convex_hull<MultiPoint, Polygon>(points);

// Simplify linestring (Douglas-Peucker)
LineString complex{{0, 0}, {1, 0.1}, {2, -0.1}, {3, 0.1}, {4, 0}};
auto simplified = complex.simplify(0.5);

// Envelope (bounding box)
LineString path{{1, 2}, {5, 8}, {3, 4}};
auto bbox = envelope<LineString, Polygon>(path);

// Centroid
Polygon triangle{{{0, 0}, {6, 0}, {3, 6}, {0, 0}}};
auto center = centroid<Polygon, Point>(triangle);  // {3, 2}
```

### Affine Transformations

Transform geometries in 2D space:

```cpp
// Translate
Point p{1, 2};
auto moved = p.translate(10, 20);  // {11, 22}

// Rotate (angle in radians)
LineString ls{{1, 0}, {2, 0}};
auto rotated = ls.rotate(M_PI / 2);  // Rotate 90 degrees

// Scale
Polygon square{{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}}};
auto scaled = square.scale(2.0, 2.0);  // Area becomes 16
```

## Requirements

- C++14 compiler (GCC 7+, Clang 6+, MSVC 2017+)
- CMake 3.15 or higher

## Third-party tools

This project would not have been possible without the following amazing tools, many thanks to its developers!

- [Catch2](https://github.com/catchorg/Catch2) - Testing framework
- [amalgamate.py](https://github.com/edlund/amalgamate) - Single-header generation
- [polyline](https://github.com/mapbox/polyline) - Google Polyline encoding

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

[MIT License](http://opensource.org/licenses/MIT)

Copyright (c) 2019 Pavel Simó

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
