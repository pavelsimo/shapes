# shapes
[![Build Status](https://travis-ci.org/pavelsimo/shapes.svg?branch=master)](https://travis-ci.org/pavelsimo/shapes)
[![Build Status](https://ci.appveyor.com/api/projects/status/nhl73vfksg69jbx2?svg=true)](https://ci.appveyor.com/project/pavelsimo/shapes)
[![codecov](https://codecov.io/gh/pavelsimo/shapes/branch/master/graph/badge.svg)](https://codecov.io/gh/pavelsimo/shapes)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://pavelsimo.github.io/shapes)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/022c774e43264ec4a04c4ccdeda9ae27)](https://www.codacy.com/app/pavelsimo/shapes?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pavelsimo/shapes&amp;utm_campaign=Badge_Grade)
[![](https://img.shields.io/github/license/pavelsimo/shapes.svg)](https://github.com/pavelsimo/shapes/blob/master/LICENSE)

A lightweight header-only geometry library for Modern C++

- Inspired by python [shapely](https://pypi.org/project/Shapely/)
- Based on OGC [Simple Features](https://en.wikipedia.org/wiki/Simple_Features)

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

## Third-party tools

This project would not have been possible without the following amazing tools, many thanks to its developers!

- [JSON for Modern C++](https://github.com/nlohmann/json)
- [amalgamate.py](https://github.com/edlund/amalgamate)
- [Catch2](https://github.com/catchorg/Catch2)
- [polyline](https://github.com/mapbox/polyline)

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
