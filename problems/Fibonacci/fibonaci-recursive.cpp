#include <iostream>

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
    std::cout << fibonacci(45) << '\n';
}