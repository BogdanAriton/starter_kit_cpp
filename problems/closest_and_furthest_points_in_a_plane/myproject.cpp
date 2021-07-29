#include "myproject.hpp"
#include <math.h>

// 0(n2) 
MainMaxPairs PointHandler::calcultateDistance(const std::vector<Point>& points) const
{
    if (points.empty()) return {};
    double minDistance, maxDistance;
    minDistance = maxDistance = distance(points[0], points[1]);
    std::pair<Point, Point> minPair = {points[0], points[1]};
    std::pair<Point, Point> maxPair = {points[0], points[1]};

    for (size_t i = 0; i < points.size()-1; ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            double currentDistance = distance(points[i], points[j]);
            if (minDistance > currentDistance) // calculating max
            {
                minDistance = currentDistance;
                minPair = {points[i], points[j]};
            }
            
            if (maxDistance < currentDistance) // calculating max
            {
                maxDistance = currentDistance;
                maxPair = {points[i], points[j]};
            }
        }
    }

    return {minPair, maxPair};
}

double PointHandler::distance(const Point& lhs, const Point& rhs) const
{
    return sqrt(std::pow((lhs.x - rhs.x), 2) + std::pow((lhs.y - rhs.y), 2));
}