#include "point_distance.hpp"

double PointsOperations::distance(const Point& p1, const Point& p2) const
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
};

pointPair PointsOperations::calculateDistance(const std::vector<Point>& points, lambda Compare) const noexcept
{
    if (points.empty()) return {};
    double distance = this->distance(points[0], points[1]);
    pointPair pointPair = {};
    // going through each pair of points to try to find the distance we need
    for (size_t i = 0; i < points.size()-1; ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            double currentDistance = this->distance(points[i], points[j]);
            if (Compare(distance, currentDistance))
            {
                distance = currentDistance;
                pointPair = {points[i], points[j]};
            }
        }
    }

    return pointPair;
}

std::pair<minPair, maxPair> PointsOperations::calculateMinMaxDistance(const std::vector<Point>& points) const noexcept
{
    if (points.empty()) return {};
    double minDistance, maxDistance;
    minDistance = maxDistance = this->distance(points[0], points[1]);
    minPair minPair = {};
    maxPair maxPair = {};
    // going through each pair of points to try to find the distance we need
    for (size_t i = 0; i < points.size()-1; ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            double currentDistance = this->distance(points[i], points[j]);
            if (minDistance > currentDistance)
            {
                minDistance = currentDistance;
                minPair = {points[i], points[j]};
            }

            if (maxDistance < currentDistance)
            {
                maxDistance = currentDistance;
                maxPair = {points[i], points[j]};
            }
        }
    }

    return {minPair, maxPair};
}
