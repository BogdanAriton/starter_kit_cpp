#include <iostream>

void func()
{
    constexpr float pi = 3.14159265;
    static_assert(( 3.1f < pi) && ( pi < 3.2f ), "Yes");
}

int main()
{
    func();
}