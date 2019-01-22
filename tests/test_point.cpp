/*
         __
   _____/ /_  ____ _____  ___  _____
  / ___/ __ \/ __ `/ __ \/ _ \/ ___/
 (__  ) / / / /_/ / /_/ /  __(__  )
/____/_/ /_/\__,_/ .___/\___/____/
                /_/

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
*/

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Point tests")
{
    SECTION("empty constructor")
    {
        Point p;
        CHECK(p.x == 0);
        CHECK(p.y == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("2d point constructor")
    {
        Point p(1, 2);
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("2d point constructor - initializer list")
    {
        Point p = {1, 2};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("3d point constructor")
    {
        Point p(1, 2, 3);
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
        CHECK(p.dimension() == 3);
    }

    SECTION("3d point constructor - initializer list")
    {
        Point p = {1, 2, 3};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
        CHECK(p.dimension() == 3);
    }

    SECTION("geometry type")
    {
        Point p;
        CHECK(p.geom_type() == GeometryType::POINT);
        CHECK(p.geom_type_str() == "POINT");
    }
}
