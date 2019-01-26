# shapes
A lightweight planar geometry library for Modern C++
 
# Design Goals



# Examples

Creating a collection of 3-dimensional points:

```cpp
MultiPoint points({{0, 0, 1}, {1, 2, 3}, {4, 5, 6}, {7, 7, 7}});
for(const auto& point: points)
{
    std::cout << point.x << " " << point.y << " " << point.z << std::endl;
} 
```

Creating geometry from GeoJSON:

```cpp
auto json = R"({"type": "Feature", "geometry": {"type": "Point", "coordinates": [125.6, 10.1] }})";
auto point = Geometry::from_geojson(json);
```

Creating geometry from WKT:

```cpp
auto point = Geometry::from_wkt("POINT (30 10)");
auto linestring = Geometry::from_wkt("LINESTRING (30 10, 10 30, 40 40)");
```
