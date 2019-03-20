#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Geometry")
{
    SECTION("Point")
    {
        SECTION("xy")
        {
//            std::unique_ptr<Geometry> geom = std::unique_ptr<Point>(new Point(1, 2));
//            CHECK(geom->type_str() == "Point");
//            CHECK(geom->type() == GeometryType::POINT);
//            CHECK(geom->detailed_type() == GeometryDetailedType::POINT);
//            CHECK(geom->ndim() == 2);
//            CHECK(geom->size() == 2);
//            CHECK(not geom->has_z());
//            CHECK(not geom->has_m());
//            CHECK(not geom->is_closed());
//            double x, y;
//            std::tie(x, y) = geom->xy()[0];
//            CHECK(x == 1.0);
//            CHECK(y == 2.0);
        }

        SECTION("xyz")
        {
//            std::unique_ptr<Geometry> geom = std::unique_ptr<Point>(new Point(1, 2, 3));
//            CHECK(geom->type_str() == "Point");
//            CHECK(geom->type() == GeometryType::POINT);
//            CHECK(geom->detailed_type() == GeometryDetailedType::POINTZ);
//            CHECK(geom->ndim() == 3);
//            CHECK(geom->has_z());
//            CHECK(geom->size() == 3);
//            CHECK(not geom->has_m());
//            CHECK(not geom->is_closed());
//            double x, y, z;
//            std::tie(x, y, z) = geom->xyz()[0];
//            CHECK(x == 1.0);
//            CHECK(y == 2.0);
//            CHECK(z == 3.0);
        }

        SECTION("xym")
        {

            /// @todo (pavel) add test
        }

        SECTION("xyzm")
        {
//            std::unique_ptr<Geometry> geom = std::unique_ptr<Point>(new Point(1, 2, 3, 4));
//            CHECK(geom->type_str() == "Point");
//            CHECK(geom->type() == GeometryType::POINT);
//            CHECK(geom->detailed_type() == GeometryDetailedType::POINTZM);
//            CHECK(geom->ndim() == 4);
//            CHECK(geom->has_z());
//            CHECK(geom->has_m());
//            CHECK(geom->size() == 4);
//            CHECK(not geom->is_closed());
//            double x, y, z, m;
//            std::tie(x, y, z, m) = geom->xyzm()[0];
//            CHECK(x == 1.0);
//            CHECK(y == 2.0);
//            CHECK(z == 3.0);
//            CHECK(m == 4.0);
        }
    }

    SECTION("MultiPoint")
    {
        /// @todo (pavel) add test
    }

    SECTION("LineString")
    {
        /// @todo (pavel) add test
    }

    SECTION("MultiLineString")
    {
        /// @todo (pavel) add test
    }

    SECTION("Polygon")
    {
        /// @todo (pavel) add test
    }

    SECTION("MultiPolygon")
    {
        /// @todo (pavel) add test
    }

}
