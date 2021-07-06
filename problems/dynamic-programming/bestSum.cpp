/*
you get a number which is the target sum
and an array of numbers from which we can compose a sum that should be equal to the target sum
we want to find out the shortest possible combination of numbers

solving the bestSum with memoization
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include <functional>

using memoMap = std::unordered_map<int, std::vector<int>>;
using cintVec = const std::vector<int>&;
using lambda = const std::function<bool(int, int)>&;

template <typename T>
void printVector(const std::vector<T>&);
std::vector<int> bestSum(const int&, cintVec, memoMap&, lambda compare);

std::vector<int> bestSum(const int& targetSum, cintVec numbers, lambda compare)
{
    memoMap memo{}; // serves as a memory buffer for calculations
    return bestSum(targetSum, numbers, memo, compare);
};

std::vector<int> bestSum(const int& targetSum, cintVec numbers, memoMap& memo, lambda compare)
{
    if (memo.find(targetSum) != memo.end()) return memo[targetSum];
    if (targetSum == 0) return {};
    if (targetSum < 0) return {-1};

    std::vector<int> shortest = {-1};

    for (auto& number : numbers)
    {
        //std::cout << number;
        auto currentSum = bestSum(targetSum - number, numbers, memo, compare);
        if (currentSum != std::vector<int>{-1})
        {
            currentSum.push_back(number);
            //printVector(currentSum);
            if (shortest == std::vector<int>{-1} || compare(currentSum.size(), shortest.size()))
                shortest = currentSum;
        }
    }
    memo[targetSum] = shortest;
    return memo[targetSum];
};

template <typename T>
void printVector(const std::vector<T>& vector)
{
    std::cout << '[' << ' ';
    for (auto &item : vector)
    {
        std::cout << item << ' ';
    }
    std::cout << ']' << '\n';
}


int main()
{
    printVector(bestSum(7, {1, 2, 3, 4, 5, 6, 7}, [](int min, int current){return min = current;}));
    printVector(bestSum(10, {1, 2, 4, 4, 5, 6, 9}, [](int min, int current){return min < current;}));
    printVector(bestSum(8, {1, 2, 4, 4}, [](int min, int current){return min < current;}));
    printVector(bestSum(100, {1, 2, 3, 4, 5, 6, 7, 15, 20, 25, 30, 50}, [](int min, int current){return min < current;}));
    printVector(bestSum(1000, {1, 2, 3, 4, 5, 6, 7, 15, 20, 25, 30, 50, 125, 140, 225}, [](int min, int current){return min < current;}));
    printVector(bestSum(4000, {1, 2, 3, 4, 5, 6, 7, 15, 20, 25, 30, 50, 125, 140, 225}, [](int min, int current){return min < current;}));
}