/*
# Coroutines
Coroutines are special functions that can have their execution suspended and resumed. 
To define a coroutine, the co_return, co_await, or co_yield keywords must be present in the function's body. 
C++20's coroutines are stackless; unless optimized out by the compiler, their state is allocated on the heap.

An example of a coroutine is a generator function, which yields (i.e. generates) a value at each invocation:
*/
#include <iostream>
#include <string>
#include <cstddef>
#include <concepts>
#include <future>
#include <functional>
#include <vector>

std::generator<int> range(T start, T end) {
  while (start < end) {
    co_yield start;
    start++;
  }

  //Implicit co_return at the end of this function:
  co_return;
}
/*
The above range generator function generates values starting at start until end (exclusive), with each iteration step yielding the current value stored in start. 
The generator maintains its state across each invocation of range (in this case, the invocation is for each iteration in the for loop). 
co_yield takes the given expression, yields (i.e. returns) its value, and suspends the coroutine at that point. Upon resuming, execution continues after the co_yield
*/

//an asynchronous computation that is executed when the task is awaited
int echo(socket s) {
  for (;;) {
    auto data = co_await s.async_read();
    co_await std::async_write(s, data);
  }

  // Implicit co_return at the end of this function:
  // co_return;
}
/*
In this example, the co_await keyword is introduced. 
This keyword takes an expression and suspends execution if the thing you're awaiting on (in this case, the read or write) 
is not ready, otherwise you continue execution. (Note that under the hood, co_yield uses co_await.)
*/

int main()
{
}

