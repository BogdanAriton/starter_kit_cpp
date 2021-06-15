#include <iostream>
#include <array>
#include <utility>

template<int T>
struct Fibo
{
    static const int val = Fibo<T-1>::val + Fibo<T-2>::val;
};

template<>
struct Fibo<0>
{
    static const int val = 0;
};

template<>
struct Fibo<1>
{
    static const int val = 1;
};

template<size_t... I>
int fib_impl(std::index_sequence<I...>, const int& i)
{
    constexpr std::array<int, sizeof...(I)> a = { Fibo<I>::val... };

    return a[i];
}

const int fib(const int i)
{
    // this will 
    return fib_impl(std::make_index_sequence<47>(), i);
}

// we would want to generate the first 45 fibonacci numbers at compile time and then run them at runtime


int main(int argc, const char*[])
{
    std::cout << fib(46) << '\n';
}