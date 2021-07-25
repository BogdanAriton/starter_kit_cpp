#include <iostream>
#include <vector>
#include "point_distance.hpp"

int main()
{
    std::vector<Point> points = {{1,4}, {4, 4}, {3, 2}, {5, 1}};
    PointsOperations distanceCalculator;

    auto minMax = distanceCalculator.calculateMinMaxDistance(points);
    std::cout << "min distance = (" << minMax.first.first << "," << minMax.first.second << ")" << '\n';
    std::cout << "max distance = (" << minMax.second.first << "," << minMax.second.second << ")" << '\n';
}