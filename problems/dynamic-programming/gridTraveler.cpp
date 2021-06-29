/*
We have to determine the number of possible paths for Start to End
This is a grid n/m
We start at the 1,1 position and end at n,m position
*/

#include <iostream>
#include <unordered_map>
using memoMap = std::unordered_map<std::string, int>;
using uint = uint64_t;

uint gridTraveler(const uint& n, const uint& m, memoMap& memo)
{
    const std::string key = std::to_string(n) + "," + std::to_string(m);
    if (memo.find(key) != memo.end()) return memo[key];
    if (n == 1 && m == 1) return 1;
    if (n == 0 || m == 0) return 0;

    memo[key] = gridTraveler(n-1, m, memo) + gridTraveler(n, m-1, memo);
    return memo[key];
}

int main()
{
    memoMap memo = {};
    std::cout << "3 by 3 grid = " << gridTraveler(3,3, memo) << '\n';
    std::cout << "2 by 3 grid = " << gridTraveler(2,3, memo) << '\n';
    std::cout << "3 by 2 grid = " << gridTraveler(3,2, memo) << '\n';
    std::cout << "10 by 10 grid = " << gridTraveler(10,10, memo) << '\n';
    std::cout << "18 by 18 grid = " << gridTraveler(18,18, memo) << '\n'; // 2333606220
}