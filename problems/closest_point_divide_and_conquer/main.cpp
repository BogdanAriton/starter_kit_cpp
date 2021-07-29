#include <iostream>
#include <vector>
#include "point_distance.hpp"
#include <chrono>

int main()
{
    std::vector<Point> points = {{1,401}, {41, 4}, {3, 21}, {5, 1}, {1,10}, {1,2}, {13, 23}, {15, 21}, {51, 5}, {5, 6}, {13, 32},
    {11,421}, {41, 43}, {31, 22}, {31,10}, {133,221}, {113, 223}, {451, 65}, {113, 322},
    {81,481}, {41, 84}, {45, 86}, {37, 217}, {75, 156}, {651,150}, {765,24}, {4513, 2343}, {5651, 765}, {345, 656}, {313, 352}};
    //std::vector<Point> points = {{2,2}, {2,5}, {6,8}, {8,5}, {9,2}, {11,3}, {9,8}, {7,4}, {5,4}, {4,4}};
    //std::vector<Point> points = {{3,3}, {4,4}, {5,6}, {5,8}, {11, 6}, {14,3}, {17,7}, {8,8}, {10,6}};
    //std::vector<Point> points =  {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    PointsOperations distanceCalculator;
    auto startDC = std::chrono::high_resolution_clock::now();
    auto min = distanceCalculator.divideAndConquer(points);
    std::cout << " divide and conquer min = " << min.first << " " << min.second << '\n';
    auto endDC = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durDC = endDC - startDC;
    std::cout << "time elapsed = " << durDC.count() << '\n';
}