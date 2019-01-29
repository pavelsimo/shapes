# shapes
[![Build Status](https://travis-ci.org/pavelsimo/shapes.svg?branch=master)](https://travis-ci.org/pavelsimo/shapes)
[![codecov](https://codecov.io/gh/pavelsimo/shapes/branch/master/graph/badge.svg)](https://codecov.io/gh/pavelsimo/shapes)
[![](https://img.shields.io/github/license/pavelsimo/shapes.svg)](https://github.com/pavelsimo/shapes/blob/master/LICENSE)

A lightweight header-only planar geometry library for Modern C++

- Inspired by python [shapely](https://pypi.org/project/Shapely/) 
- Complaint with OGC [Simple Features](https://en.wikipedia.org/wiki/Simple_Features)

## Installation

`shapes` ships as a header-only library:

```cpp
#include <simo/shapes.hpp>

using namespace simo::shapes;
```

## Examples

Building a point from GeoJSON:

```cpp
auto p = Point::from_json("{\"type\": \"Point\", \"coordinates\": [1.0, 2.0, 3.0]}");
std::cout << p.x << " " << p.y << " " << p.z << std::endl;
std::cout << p.to_json() std::endl; 
```

Iterating a `MultiPoint` is as simple as:

```cpp
MultiPoint points({{0, 0, 1}, {1, 2, 3}, {4, 5, 6}, {7, 7, 7}});
for(const auto& point: points)
{
    std::cout << point.x << " " << point.y << " " << point.z << std::endl;
} 
```

## Third-party tools

This project would not have been possible without the following amazing tools, many thanks to its developers!

- [JSON for Modern C++](https://github.com/nlohmann/json)
- [amalgamate.py](https://github.com/edlund/amalgamate)
- [Catch2](https://github.com/catchorg/Catch2)

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
