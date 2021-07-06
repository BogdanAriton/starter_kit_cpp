#ifndef BOOK_ORDER
#define BOOK_ORDER

#include <string>
#include <unordered_map>
#include <algorithm>
#include "entry-data.h"
#include "output.h"

class Order
{
public:
    virtual ~Order() {};
    Order(int targetSize, Type type): targetSize(targetSize), type(static_cast<char>(type)) {};
    const std::unordered_map<std::string, EntryData>& operator()() const noexcept { return orders;};

    void add(const EntryData& entry) noexcept
    {
        if (isEntryPresent(entry.orderID)) return;
        orders.insert({entry.orderID, entry});
        shareCount += entry.size;
    }

    void update(const EntryData& entry) noexcept
    {
        if (!isEntryPresent(entry.orderID)) return;
        if (orders[entry.orderID].size > entry.size) orders[entry.orderID].size -= entry.size;
        else orders.erase(entry.orderID);
        shareCount -= entry.size;
    }

    bool isEntryPresent(const std::string& entry) const noexcept
    {
        return (orders.find(entry) != orders.end());
    }

    virtual bool sortComparator(const std::pair<double, int> &lhs, const std::pair<double, int> &rhs) const noexcept = 0;
    int getShareCount() const noexcept { return shareCount; }
    void setNAFlag(bool flag) noexcept { this->NAFlag = flag; };
    bool getNAFlag() const noexcept { return this->NAFlag; };
    void setCurrentIncome(double newIncome) noexcept { this->currentIncome = newIncome; };
    double getCurrentIncome() const noexcept { return this->currentIncome; };
    char getType() const noexcept { return this->type; }
    int getTargetSize() const noexcept { return this->targetSize; }

protected:
    std::unordered_map<std::string, EntryData> orders{};
    double currentIncome = 0;
    int targetSize = 0;
    int shareCount = 0;
    bool NAFlag = false;
    std::string lastVerifiedTimeStamp;
    char type;
};

class Asks : public Order
{
public:
    Asks(int targetSize): Order(targetSize, Type::bid) {};
    bool sortComparator(const std::pair<double, int> &lhs, const std::pair<double, int> &rhs) const noexcept override
    {
        return lhs.first < rhs.first;
    };

    Asks(const Asks&) = delete;
    Asks& operator=(const Asks&) = delete;
    Asks(Asks&&) = default;
    Asks& operator=(Asks&&) = default;
};

class Bids : public Order
{
public:
    Bids(int targetSize): Order(targetSize, Type::ask) {};
    bool sortComparator(const std::pair<double, int> &lhs, const std::pair<double, int> &rhs) const noexcept override
    {
        return lhs.first > rhs.first;
    };

    Bids(const Bids&) = delete;
    Bids& operator=(const Bids&) = delete;
    Bids(Bids&&) = default;
    Bids& operator=(Bids&&) = default;
};

#endif