#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPoint tests")
{
    SECTION("geometry type")
    {
        MultiPoint mp;
        CHECK(mp.type() == GeometryType::MULTIPOINT);
        CHECK(mp.type_str() == "MultiPoint");
    }

    SECTION("multipoint empty")
    {
        MultiPoint mp;
        CHECK(mp.empty());
    }

    SECTION("multipoint not empty")
    {
        MultiPoint mp = {{1.0, 2.0}, {2.0, 3.0}};
        CHECK(!mp.empty());
    }

    SECTION("2d multipoint constructor - initializer list <double>")
    {
        MultiPoint mp = {{1.0, 2.0}, {2.0, 3.0}};
        CHECK(mp[0].x == 1.0);
        CHECK(mp[0].y == 2.0);
        CHECK(mp[1].x == 2.0);
        CHECK(mp[1].y == 3.0);
    }

    SECTION("3d multipoint constructor - initializer list <double>")
    {
        MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        CHECK(mp[0].x == 1.0);
        CHECK(mp[0].y == 2.0);
        CHECK(mp[0].z == 3.0);
        CHECK(mp[1].x == 4.0);
        CHECK(mp[1].y == 5.0);
        CHECK(mp[1].z == 6.0);
    }

    SECTION("2d multipoint - bounds")
    {
        MultiPoint mp = {{1.0, 2.0}, {3.0, 4.0}};
        CHECK(mp.bounds.maxx == 3.0);
        CHECK(mp.bounds.maxy == 4.0);
        CHECK(mp.bounds.minx == 1.0);
        CHECK(mp.bounds.miny == 2.0);
    }

    SECTION("2d multipoint - for each")
    {
        auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        int n   = 0;
        for (const auto& p : mp)
        {
            CHECK(p.x != 0);
            CHECK(p.y != 0);
            ++n;
        }
        CHECK(n == 3);
    }

    SECTION("3d multipoint - for each")
    {
        auto mp = MultiPoint{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
        int n   = 0;
        for (const auto& p : mp)
        {
            CHECK(p.x != 0);
            CHECK(p.y != 0);
            CHECK(p.z != 0);
            ++n;
        }
        CHECK(n == 3);
    }

    SECTION("2d multipoint - index operator")
    {
        auto points = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
        auto p1     = points[0];
        auto p2     = points[1];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p2.x == 3.0);
        CHECK(p2.y == 4.0);
    }

    SECTION("3d multipoint - index operator")
    {
        auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        auto p1 = mp[0];
        auto p2 = mp[1];
        auto p3 = mp[2];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p2.x == 3.0);
        CHECK(p2.y == 4.0);
        CHECK(p3.x == 5.0);
        CHECK(p3.y == 6.0);
    }

    SECTION("2d multipoint - from json")
    {
        std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0],[3.0,4.0]]})";
        auto mp          = MultiPoint::from_json(json);
        auto p1          = mp[0];
        auto p2          = mp[1];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p2.x == 3.0);
        CHECK(p2.y == 4.0);
    }

    SECTION("3d multipoint - from json")
    {
        std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})";
        auto mp          = MultiPoint::from_json(json);
        auto p1          = mp[0];
        auto p2          = mp[1];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p1.z == 3.0);
        CHECK(p2.x == 4.0);
        CHECK(p2.y == 5.0);
        CHECK(p2.z == 6.0);
    }

    SECTION("2d multipoint - json")
    {
        MultiPoint mp = {{1.0, 2.0}, {3.0, 4.0}};
        mp.precision  = 1;
        CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1.0,2.0],[3.0,4.0]]})");
    }

    SECTION("3d multipoint - json")
    {
        MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        mp.precision  = 1;
        CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})");
    }

    SECTION("2d multipoint - io")
    {
        MultiPoint mp = {{1.0, 2.0}, {4.0, 5.0}};
        mp.precision  = 1;
        CHECK(mp.wkt() == "MULTIPOINT((1.0 2.0),(4.0 5.0))");
    }
}
