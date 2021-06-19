/*
A simple implementaiton of stack
Stacks can be implemented using arrays and also linked lists
Array implementation:
    - we can just use an array and use stack operations on it

Stack operations:
    - Push - add to the top
    - Pop - removes the top element
    - Top - get the top element
*/
#include <iostream>
#include <stack>
#include <vector>
#include <list>

int main()
{
    // a stack implementation is already available in the standard library: std::stack
    // it's a template thus it can take any type
    // It's actually an adapter over either a deque or vector or list
        // meaning you can create a stack that will use either a deque (which is the default) or vector, or list or a custom implementation that implement push_back or push_front, pop and top
    
    // stack using vector
    std::stack<char, std::vector<char>> vecStack;

    // stack using deque
    std::stack<char> defaultStack;

    // stack using list
    std::stack<char, std::list<char>> listStack;

    // see check-bracket-problem.cpp in the problems folder for a stack example

}

