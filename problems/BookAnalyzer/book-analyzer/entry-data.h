
#ifndef BOOK_ENTRY_DEF
#define BOOK_ENTRY_DEF

#include <string>
#include <numeric>
#include <cmath>
enum class Type : char
{
    ask = 'S',
    bid = 'B',
    any = '\0'
};

struct EntryData
{
    std::string timeStamp{};
    char action = '\0';
    std::string orderID{};
    char type = '\0';
    double price = 0;
    int size = 0;

    bool isEmpty() const noexcept
    {
        return timeStamp.empty() && (action == '\0') && orderID.empty();
    };
};

constexpr int UNITS_LAST_PLACE = 2;
bool isEqual(double lhs, double rhs) noexcept
{
    /* using epsilon to determine the equality with specific precision units */
    return (std::fabs(lhs - rhs) <= std::numeric_limits<double>::epsilon() * std::max(std::fabs(lhs), std::fabs(rhs)) * UNITS_LAST_PLACE);    
}

inline bool operator==(const EntryData& lhs, const EntryData& rhs) noexcept
{
    return (lhs.timeStamp == rhs.timeStamp && 
            lhs.action == rhs.action && 
            lhs.orderID == rhs.orderID && 
            lhs.type == rhs.type &&
            isEqual(lhs.price, rhs.price) &&
            lhs.size == rhs.size);
};

#endif