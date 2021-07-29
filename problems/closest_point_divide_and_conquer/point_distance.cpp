#include "point_distance.hpp"
#include <algorithm>
#include <iostream>

double PointsOperations::distance(const Point& p1, const Point& p2) const
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
};

pointPair PointsOperations::divideAndConquer(const std::vector<Point>& points) const
{
    if (points.empty()) return {};

    // we make a copy of the vector for points ordered ont he X axis
    std::vector<Point> X(points);
    std::sort(begin(X), end(X), [](const Point& first, const Point& last){ return first.x < last.x; });

    // we make a copy of the vector for points ordered ont he Y axis
    std::vector<Point> Y(points);
    std::sort(begin(Y), end(Y), [](const Point& first, const Point& last){ return first.y < last.y; });

    pointPair minPoints = {};
    recursiveDivideAndConquer(X, 0 , X.size()-1, minPoints, Y);

    return minPoints;
}

double PointsOperations::recursiveDivideAndConquer(const std::vector<Point>& points, size_t start, size_t end, pointPair& pair, const std::vector<Point>& Y) const
{
    // the exit point is if we have 3 or 2 points left
    if ((end - start) <= 3) return bruteForce( points, start, end , pair);
    size_t middle = start + ((end - start)/2);
    double distanceLeft = recursiveDivideAndConquer(points, start, middle - 1, pair, Y);
    pointPair leftPair = pair;
    double distanceRight = recursiveDivideAndConquer(points, middle, end, pair, Y);
    pointPair rightPair = pair;

    double delta = distanceRight;
    pair = rightPair;
    if (distanceLeft <= distanceRight)
    {
        pair = leftPair;
        delta = distanceLeft;
    }
    // in the middle point we have the imaginary line
    auto pointsInDeltaSection = getPointsInDeltaSection(Y, delta);

    // we have to go through each point in the delta section and for each point try to find a new point that is closer than delta
    for (size_t i = 0; i < pointsInDeltaSection.size() -1 ; ++i)
    {
        // we then iterate through the points that are not further then delta
        // we're checking pairs thus we will start from i + 1 ( this way we don't check a pair twice )
        for (size_t j = i+1; j < pointsInDeltaSection.size() && 
        (pointsInDeltaSection[i].y - pointsInDeltaSection[j].y) < delta; ++j)
        // here is the catch - because we're reducing the area for each point to be between delta up down left right - then we can have a maximum of 8 points to look through
        {
            // we have found a new smallest distance
            double currentDistance = distance(pointsInDeltaSection[i], pointsInDeltaSection[j]);
            if (delta > currentDistance)
            {
                delta = currentDistance;
                pair = {pointsInDeltaSection[i], pointsInDeltaSection[j]};
            }
        }
    }
    return delta;
}

std::vector<Point> PointsOperations::getPointsInDeltaSection(const std::vector<Point>& points, double delta) const
{
    size_t middle = (points.size())/2;
    Point middlePoint = points[middle];
    std::vector<Point> deltaSection{};

    for (auto& point : points)
    {
        if (abs(point.x - middlePoint.x) <= delta)
        {
            deltaSection.push_back(point);
        }
    }

    return deltaSection;
}

double PointsOperations::bruteForce(const std::vector<Point>& points, size_t start, size_t end, pointPair& pair) const noexcept
{
    if (points.empty()) return {};
    double distance = this-> distance(points[0], points[1]);
    pair = {points[0], points[1]};
    // going through each pair of points to try to find the distance we need
    for (size_t i = start; i < end; ++i)
    {
        for (size_t j = i + 1; j <= end; ++j)
        {
            double currentDistance = this->distance(points[i], points[j]);
            //std::cout << "brute force points: " << points[i] << points[j] << '\n';
            if ( distance > currentDistance)
            {
                distance = currentDistance;
                pair = {points[i], points[j]};
            }
        }
    }
    return distance;
}