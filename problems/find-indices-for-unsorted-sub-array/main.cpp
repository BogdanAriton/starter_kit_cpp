#include <iostream>
#include <vector>
#include <functional>

template <typename Iterator>
Iterator getIndices(Iterator&& sItr, Iterator&& eItr, std::function<bool(int, int)> comp);

int main()
{
    std::vector<int> numbers = { 1, 2, 3, 3, 7, 9, 10, 5, 6, 12, 8, 13, 14};

    auto start = getIndices(numbers.begin(), numbers.end(), [](int a, int b){ return a > b; });
    auto end = getIndices(numbers.rbegin(), numbers.rend(), [](int a, int b){ return a < b; });

    std::cout << "Start Indice = " << std::distance(numbers.begin(), start) << '\n';
    std::cout << "End Indice = " << std::distance(end, numbers.rend()) << '\n';
    std::cout << "Start value = " << *start << '\n';
    std::cout << "End value = " << *end << '\n';
}

template <typename Iterator>
Iterator getIndices(Iterator&& sItr, Iterator&& eItr, std::function<bool(int, int)> comp)
{
    auto result = eItr;
    auto keepStart = sItr;
    for (;sItr != eItr-1; ++sItr)
    {
        auto next = sItr + 1;
        if (comp(*sItr,*next))
        {
            // we stop here since the array is no longer in order
            auto start = keepStart;
            for (; start != next; ++start)
            {
                if (comp(*start,*next))
                {
                    if (result == eItr) result = start;
                    if (comp(*result,*start)) result = start;
                    break;
                }
            }
        }
    }
    
    return result;
}