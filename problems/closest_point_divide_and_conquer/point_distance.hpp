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
    double recursiveDivideAndConquer(const std::vector<Point>& points, size_t start, size_t end, pointPair& pair, const std::vector<Point>& Y) const;
    std::vector<Point> getPointsInDeltaSection(const std::vector<Point>& points, double delta) const;
    double bruteForce(const std::vector<Point>& points, size_t start, size_t end, pointPair& pair) const noexcept;
public:
    double distance(const Point&, const Point&) const;
    pointPair divideAndConquer(const std::vector<Point>& points) const;
};

#endif //POINT_DISTANCE