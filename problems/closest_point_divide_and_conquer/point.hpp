#include <ostream>

struct Point
{
    int x;
    int y;

};

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline std::ostream& operator<<( std::ostream& o, const Point& rhs)
{
    return o << "[" << rhs.x << "," << rhs.y << "]";
}