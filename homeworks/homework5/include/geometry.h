#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace homework5 {
    enum class GeometryType: uint_least32_t {Point = 1, Line, Curve};

    class GeometricPrimitive {
    public:
        virtual GeometryType type() const = 0;
        virtual ~GeometricPrimitive() = default;

        friend std::ostream& operator<< (std::ostream& os, const GeometricPrimitive& pr);
    };

    using Primitives = std::vector<std::unique_ptr<GeometricPrimitive> >;
    using Coordinate = std::uint_least32_t;

    class Point: public GeometricPrimitive {
    public:
        Point() : _x{0}, _y{0} {}
        Point(std::uint_least32_t x, std::uint_least32_t y): _x{x}, _y{y} {}

        Point(Point&&) = default;
        Point& operator=(Point &&) = default;

        Point(const Point&) = default;
        Point& operator=(const Point&) = default;

        GeometryType type() const override {
            return GeometryType::Point;
        }

    private:
        Coordinate _x, _y;
    };

    class Line: public GeometricPrimitive {
    public:
        Line(Point start, Point end): _start {std::move(start)}, _end {std::move(end)} {}
        Line(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) : _start{x1, y1}, _end{x2, y2} {}

        Line(const Line&) = default;
        Line& operator=(const Line&) = default;

        Line(Line&&) = default;
        Line& operator=(Line&&) = default;

        GeometryType type() const override {
            return GeometryType::Line;
        }
    private:
        Point _start;
        Point _end;
    };

//    class Curve: public GeometricPrimitive {
//    public:
//        GeometryType type() const override {
//            return GeometryType::Curve;
//        }
//    private:
//        std::vector<Point> _controlPoints;
//    };
}