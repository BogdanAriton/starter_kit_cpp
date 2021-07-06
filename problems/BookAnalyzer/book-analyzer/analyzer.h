#ifndef ANALYZER_DEF
#define ANALYZER_DEF

#include <numeric>
#include "entry-data.h"
#include "orders.h"
#include "output.h"

enum class Action : char
{
    add = 'A',
    update = 'R',
    analyze = '\0'
};


template <enum Action>
struct Analyzer {};

template<>
struct Analyzer<Action::add>
{
    static void execute(const EntryData& data, Order& order)
    {
        order.add(data);
    }
};

template<>
struct Analyzer<Action::update>
{
    static void execute(const EntryData& data, Order& order)
    {
        order.update(data);
    };
};

template<>
struct Analyzer<Action::analyze>
{
    /* 
        Analyzer is in charge of decideing what and when to print
        It can print either:
        - nothing - in the case the income doesn't changes
        - Curent Data time + Type + NA - in case a new calculation cannot be made, but a previous one was made
        - Curent Data time + Type + result - in case we can calculate a result and it's different from previous one
    */
    static OutputData execute(const EntryData& entry, Order& order)
    {
        OutputData outdata;
        outdata.timeStamp = entry.timeStamp;
        outdata.type = order.getType();

        if (order.getShareCount() < order.getTargetSize())
        {
            if (order.getCurrentIncome() > 0 && order.getNAFlag()) 
            {
                outdata.action = PrintAction::dontPrint;
                return outdata;
            }
            if (order.getCurrentIncome() > 0 && !order.getNAFlag()) 
            {
                order.setNAFlag(true);
                outdata.action = PrintAction::printNA;
                return outdata;
            }
            if (order.getCurrentIncome() == 0) outdata.action = PrintAction::dontPrint;
            return outdata;
        }

        auto orders = order();
        std::vector<std::pair<double, int>> currentOrders{};
        for (auto& item : orders)
        {
            currentOrders.push_back({item.second.price, item.second.size});
        }
        std::sort(begin(currentOrders), end(currentOrders),
                  [&](const std::pair<double, int> &lhs, const std::pair<double, int> &rhs)
                  { return order.sortComparator(lhs, rhs);});

        double newIncome = calculateNextIncome(currentOrders, order.getTargetSize());
        if (!order.getNAFlag() && isEqual(order.getCurrentIncome(), newIncome))
        {
            outdata.action = PrintAction::dontPrint;
            return outdata;
        }

        order.setCurrentIncome(newIncome);
        order.setNAFlag(false);
        outdata.value = newIncome;
        outdata.action = PrintAction::printValue;
        return outdata;
    };

private:

    /* Calculates the new income for the current entry */
    static double calculateNextIncome(const std::vector<std::pair<double, int>>& currentOrders, int targetSize) noexcept
    {
        int remainder = targetSize;
        double result = 0;
        for (auto& item : currentOrders)
        {
            if (remainder == 0) return result;
            if (item.second <= remainder)
            {
                result += item.first * double(item.second);
                remainder -= item.second;
            }
            else
            {
                result += item.first * double(remainder);
                return result;
            }
        }
        return result;
    }
};

#endif