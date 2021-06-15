/*
how to iterate through a tuple
*/

#include <iostream>
#include <tuple>
#include <string>
#include <utility> 

template <std::size_t I = 0, typename...Args>
inline typename std::enable_if<I == sizeof...(Args), void>::type
printTuple(const std::tuple<Args...>& tuple)
{
    return;
};

template <std::size_t I = 0, typename...Args>
inline typename std::enable_if<I < sizeof...(Args), void>::type
printTuple(const std::tuple<Args...>& tuple)
{
    std::cout << std::get<I>(tuple) << '\n';
    printTuple<I+1>(tuple);
};


int main()
{
    auto tuple = std::make_tuple( 1,2,3,4,4,5,6,6,5.3442 );
    printTuple(tuple);
}