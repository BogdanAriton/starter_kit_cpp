/*
The idea behind it is to have a more descriptive way of knowing what we are constructing

Factory Method:
    A function that creates objects.

Abstract Factory:
    It's abstract class the create an hierarchy of classes
*/


#include <cmath>
#include <iostream>

// Example of factory method
class Point
{
    Point(float x, float y) : x(x), y(y) {};

    class PointFactory
    {
    public:
        static Point NewCartision(const float x, const float y)
        {
            return {x, y};
        };

        static Point NewPolar(const float r, const float theta)
        {
            return {r * cos(theta), r * sin(theta)};
        };
    };

public:
    float x,y;
    static PointFactory Factory;
};

// Factory example - this is a separated component
// sometimes we would need to send the factory somewhere, we would need to pass it as a param
// class PointFactory
// {
// public:
//     static Point NewCartision(const float x, const float y)
//     {
//         return {x, y};
//     };

//     static Point NewPolar(const float r, const float theta)
//     {
//         return {r * cos(theta), r * sin(theta)};
//     };
// };

int main()
{
    // auto c = PointFactory::NewCartision(1, 2);
    // auto p = PointFactory::NewPolar(5, 4);

    auto p = Point::Factory.NewCartision(1, 2);
    

}