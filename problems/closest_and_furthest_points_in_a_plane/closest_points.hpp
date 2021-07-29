#ifndef PointHandler_
#define PointHandler_

#include <vector>
#include <utility>
#include <ostream>

struct Point
{
    int x;
    int y;
};

inline std::ostream& operator<<(std::ostream& ost, const Point& point)
{
    return ost << "[" << point.x << "," << point.y << "]";
}

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator==(const std::pair<Point, Point>& lhs, const std::pair<Point, Point>& rhs)
{
    return (lhs == rhs) && (lhs == rhs);
}

struct MainMaxPairs
{
    std::pair<Point, Point> min;
    std::pair<Point, Point> max;
};

inline std::ostream& operator<<(std::ostream& ost, const std::pair<Point, Point>& point)
{
    return ost << "[" << point.first << "," << point.second << "]";
}

class PointHandler
{
    double distance(const Point& lhs, const Point& rhs) const;
public:
    MainMaxPairs calcultateDistance(const std::vector<Point>& points) const;
};

#endif