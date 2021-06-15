#include <iostream>

// this is a functor
struct add_x { // this is a constexpr because it can be evaluated at compile time
  constexpr add_x(int val) : x(val) {}  // Constructor
  constexpr int operator()(int y) const { return x + y; } 

private:
  int x;
};

int main()
{
    constexpr add_x adder(10);
    std::cout << adder(20) << '\n'; // prints 30 (will add 10 + 20)
}