#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <type_traits>

constexpr char str[] = "std::string cannot be constexpr";

int main()
{
    std::string str = R"(
        this is a string with
        several
        lines
    )";

    //this will get all the words in the string
    std::istringstream stream1(str);
    std::string buffer;
    while (stream1 >> buffer)
    {
        std::cout << buffer << '\n';
    }
    buffer.clear();
    // this will get all the different lines in the string
    std::istringstream stream2(str);
    while (std::getline(stream2, buffer, '\n'))
    {
        buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
        std::cout << buffer << '\n';
    }
    std::cout << '\n';

    std::string a = "      ala bala porto cala      x";
    std::vector<char> v{};
    for (auto& c : a)
    {
        v.push_back(c);
    }
    for (auto& item : v)
    {
        std::cout  << item;
    }
    std::cout << '\n';
    a.erase(std::remove(a.begin(), a.end(), ' '), a.end());
    
    std::cout << a << '\n';

    v.erase(std::remove(v.begin(), v.end(), ' '), v.end());
    for (auto& item : v)
    {
        std::cout  << item;
    }

}

