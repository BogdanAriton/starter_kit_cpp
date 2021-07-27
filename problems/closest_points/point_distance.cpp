#include "point_distance.hpp"
#include <algorithm>
#include <iostream>

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
    minPair minPair = {points[0], points[1]};
    maxPair maxPair = {points[0], points[1]};
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

pointPair PointsOperations::divideAndConquer(const std::vector<Point>& points) const
{
    if (points.empty()) return {};

    // we make a copy of the vector for points ordered ont he X axis
    std::vector<Point> X(points);
    std::sort(begin(X), end(X), [](const Point& first, const Point& last){ return first.x < last.x; });

    // we make a copy of the vector for points ordered ont he Y axis
    std::vector<Point> Y(points);
    std::sort(begin(Y), end(Y), [](const Point& first, const Point& last){ return first.y < last.y; });

    return recursiveDivideAndConquer(X, Y);
}

std::vector<Point> PointsOperations::getPointsInDeltaSection(const std::vector<Point>& points, double delta) const
{
    size_t middle = (points.size())/2;
    //std::cout << "middle " << middle << '\n';
    Point middlePoint = points[middle];
    //std::cout << "middlePoint " << middlePoint << '\n';
    std::vector<Point> deltaSection{};

    for (auto& point : points)
    {
        if (abs(point.x - middlePoint.x) <= delta)
        {
            deltaSection.push_back(point);
        }
    }
    //for (auto& item : deltaSection) std::cout << item << '\n';
    return deltaSection;
}

double PointsOperations::recursiveDivideAndConquer(const std::vector<Point>& points, size_t start, size_t end, pointPair& pair) const
{
    // the exit point is if we have 3 or 2 points left
    if ((end - start) <= 3) return bruteForce( points, start, end , pair);
    size_t middle = start + ((end - start)/2);
    double distanceLeft = recursiveDivideAndConquer(points, start, middle - 1, pair);
    pointPair leftPair = pair;
    //std::cout << "left pair found = " << leftPair.first << leftPair.second << " ";
    //std::cout << '\n';
    double distanceRight = recursiveDivideAndConquer(points, middle, end, pair);
    pointPair rightPair = pair;
    //std::cout << "right pair found = " << rightPair.first << rightPair.second << " ";
    //std::cout << '\n';
    
    if (distanceLeft <= distanceRight)
    {
        pair = leftPair;
        return distanceLeft;
    }
    else
    {
        pair = rightPair;
        return distanceRight;
    }
}

pointPair PointsOperations::recursiveDivideAndConquer(const std::vector<Point>& X, const std::vector<Point>& Y) const
{
    pointPair minPoints = {};
    double delta = recursiveDivideAndConquer(X, 0 , X.size()-1, minPoints);
    // in the middle point we have the imaginary line
    //std::cout << "minPoints " << minPoints.first << minPoints.second << '\n';
    //std::cout << "delta " << delta << '\n';
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
                minPoints = {pointsInDeltaSection[i], pointsInDeltaSection[j]};
            }
        }
    }

    return minPoints;
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