#include <iostream>
#include <array>
#include <utility>

template<uint64_t T>
struct Fibo
{
    static const uint64_t val = Fibo<T-1>::val + Fibo<T-2>::val;
};

template<>
struct Fibo<0>
{
    static const uint64_t val = 0;
};

template<>
struct Fibo<1>
{
    static const uint64_t val = 1;
};

template<size_t... I>
int fib_impl(std::index_sequence<I...>, const uint64_t& i)
{
    constexpr std::array<uint64_t, sizeof...(I)> a = { Fibo<I>::val... };

    return a[i];
}

const int fib(const uint64_t i)
{
    // this will 
    return fib_impl(std::make_index_sequence<51>(), i);
}

// we would want to generate the first 45 fibonacci numbers at compile time and then run them at runtime


int main(int argc, const char*[])
{
    std::cout << fib(50) << '\n';
}