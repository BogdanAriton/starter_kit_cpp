#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

// template <typename...Args>
// auto to_string(const Args& ...params) -> std::vector<std::string>
// {   
//     return {[](const auto& p) {
//         std::stringstream ss;
//         ss << p;
//         return ss.str();
//     }(params)...}; // this implementation is not preffered due to the fact that a new lambda will be created for each param in pack
// }

template <typename...Args>
auto to_string(const Args& ...params) -> std::vector<std::string>
{
    const auto to_str = [](const auto& p) {
        std::stringstream ss;
        ss << p;
        return ss.str();
    };
    return {to_str(params)...};
}

int main()
{
    for (const auto& item : to_string(1,2,3,4,4,5,65,67,7))
    {
        std::cout << item << '\n';
    }
    return 0;
}