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
#ifndef SIMO_SHAPES_H
#define SIMO_SHAPES_H

#include <string>
#include <tuple>
#include <memory>
#include <vector>

namespace simo {
namespace shapes {

    // WktReader / WktWriter
    // GeojsonReader / GeojsonWriter
    // WkbReader / WkbWriter


    enum class GeometryType {
        POINT,
        MULTIPOINT,
        LINESTRING,
        MULTILINESTRING,
        POLYGON,
        MULTIPOLYGON,
        GEOMETRYCOLLECTION
    };

    struct BoundingBox {
        double xmin, ymin, xmax, ymax;
    };

    class Geometry {
    public:
        Geometry() = default;

        virtual GeometryType geom_type() const noexcept = 0;
        virtual std::string geom_str() const noexcept = 0;
        //virtual BoundingBox bounds() const = 0;

//        virtual std::tuple<double, double, double, double> bounds();
//
//        virtual std::string to_geojson();
//        virtual Geometry* from_geojson(const string& json);
//
//        virtual std::string to_wkt();
//        virtual Geometry* from_wkt(const string& wkt);
//
//        virtual std::string to_wkb();
//        virtual Geometry* from_wkb(const string& wkb);

        virtual ~Geometry() = default;
    };

    class Coordinate {
    public:
        double x, y, z;
    };

    class Point : public Geometry {

    public:
        Point() = default;

        GeometryType geom_type() const override {
            return GeometryType::POINT;
        }

        std::string geom_str() const override {
            return "Point";
        }
    private:
        Coordinate m_coordinate;
    };

    class MultiPoint : public Geometry {
    public:
        GeometryType geom_type() const override {
            return GeometryType::MULTIPOINT;
        }

        std::string geom_str() const override {
            return "MultiPoint";
        }
    };

    class LineString : public Geometry {
    public:
        GeometryType geom_type() const override {
            return GeometryType::LINESTRING;
        }

        std::string geom_str() const override {
            return "LineString";
        }
    };

    class MultiLineString : public Geometry {
    public:
        GeometryType geom_type() const override {
            return GeometryType::MULTILINESTRING;
        }

        std::string geom_str() const override {
            return "MultiLineString";
        }
    };

    class Polygon : public Geometry {
    public:
        GeometryType geom_type() const override {
            return GeometryType::POLYGON;
        }

        std::string geom_str() const override {
            return "Polygon";
        }
    };

    class MultiPolygon : public Geometry {
    public:
        GeometryType geom_type() const override {
            return GeometryType::MULTIPOLYGON;
        }

        std::string geom_str() const override {
            return "MultiPolygon";
        }
    };

} // namespace shapes
} // namespace simo

#endif //SIMO_SHAPES_H
