// best solution

#include <cmath>
#include <iostream>

static const auto sqrt_5 = std::sqrt(5);

constexpr uint64_t fib(const int i)
{
    if (i == 0) return 0;
    if (i == 1) return 1;

    return static_cast<uint64_t>((std::pow(1 + sqrt_5, i) - std::pow(1 - sqrt_5, i)) / (std::pow(2, i) * sqrt_5));
}

int main()
{
    std::cout << fib(100) << '\n';

}