// best solution

#include <cmath>
#include <iostream>
#include <chrono>

static const double sqrt_5 = std::sqrt(5);

constexpr uint64_t fib(const int i)
{
    if (i == 0) return 0;
    if (i == 1) return 1;

    return static_cast<uint64_t>((std::pow(1 + sqrt_5, i) - std::pow(1 - sqrt_5, i)) / (std::pow(2, i) * sqrt_5));
}

int main()
{
    volatile int value = 50;
    auto start = std::chrono::steady_clock::now();
    std::cout << "fibonacci formula for " << value << " = " << fib(value) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << "time elapsed = " << duration.count() << '\n';
}