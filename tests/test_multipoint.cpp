#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPoint")
{
    SECTION("Test Initializer List")
    {
        Point p(1, 2, 3);
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
    }
    
//    using namespace simo::shapes;
//
//    int main()
//    {
//        auto json = R"({"type": "Feature", "geometry": {"type": "Point", "coordinates": [125.6, 10.1] }})";
//
//        MultiPoint multipoint1({{0, 0, 1}, {1, 2, 3}, {4, 5, 6}, {7, 7, 7}});
//        for(const auto& point: multipoint1)
//        {
//            std::cout << point.x << " " << point.y << " " << point.z << std::endl;
//        }
//        std::cout << std::endl;
//
//        std::vector<Point> point_list;
//        point_list.push_back({4, 7, 2});
//        point_list.push_back({9, 8, 7});
//        point_list.push_back({1, 2, 3});
//
//        MultiPoint multipoint2(point_list);
//        for(const auto& point: multipoint2)
//        {
//            std::cout << point.x << " " << point.y << " " << point.z << std::endl;
//        }
//
//    }
}
