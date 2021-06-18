#include <iostream>
#include <chrono>

// make the recursive version a constexpr instead of leaving it like it is
// why?

constexpr uint64_t fibonacci(int no)
{
    if (no == 0) return 0;
    if (no == 1) return 1;
    return fibonacci(no-1) + fibonacci(no-2);
}

int main(int argc, const char*[] )
{
    volatile int value = 50;
    auto start = std::chrono::steady_clock::now();
    std::cout << "fibonacci recursive: " << value << " = " << fibonacci(value) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "time elapsed: " << duration.count() << " sec" << '\n';
}