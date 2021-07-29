/*
vector<Point> = {{1, 4}, {4,4}, {3,2}, {5,1}}

*/
#include <vector>
#include <iostream>
#include "myproject.hpp"

int main()
{
    std::vector<Point> pointsVec = {{1, 4}, {4,4}, {3,2}, {5,1}};
    PointHandler pointHandler;
    auto result = pointHandler.calcultateDistance(pointsVec);

    std::cout << "The result is: min pair = " << result.min << " max pair = " << result.max << '\n';
}