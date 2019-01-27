# shapes
A lightweight header-only planar geometry library for Modern C++
 
## Examples

Building a point from GeoJSON:

```cpp
auto p = Point::from_json("{\"type\": \"Point\", \"coordinates\": [1.0, 2.0, 3.0]}");
std::cout << p.x << " " << p.y << " " << p.z << std::endl;
std::cout << p.to_json() std::endl; 
```

Building geometry from WKT:

```cpp
auto point = Geometry::from_wkt("POINT (30 10)");
auto linestring = Geometry::from_wkt("LINESTRING (30 10, 10 30, 40 40)");
```

Iterating a `MultiPoint` is as simple as:

```cpp
MultiPoint points({{0, 0, 1}, {1, 2, 3}, {4, 5, 6}, {7, 7, 7}});
for(const auto& point: points)
{
    std::cout << point.x << " " << point.y << " " << point.z << std::endl;
} 
```

## License

MIT License

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