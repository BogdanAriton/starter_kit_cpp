#ifndef POINT_DISTANCE
#define POINT_DISTANCE

#pragma once

#include <math.h>
#include <vector>
#include <functional>
#include "point.hpp"

using pointPair = std::pair<Point, Point>;
using lambda = const std::function<bool(double, double)>&;
using minPair = std::pair<Point, Point>;
using maxPair = std::pair<Point, Point>;

class PointsOperations
{
public:
    double distance(const Point&, const Point&) const;
    pointPair calculateDistance(const std::vector<Point>& points, lambda Compare) const noexcept;
    std::pair<minPair, maxPair> calculateMinMaxDistance(const std::vector<Point>& points) const noexcept;
};

#endif //POINT_DISTANCE