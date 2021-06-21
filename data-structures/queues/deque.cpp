/*
Standard offers a double ended queue implementation
As opposed to a singly linked list the double ended 
*/

#include <iostream>
#include <deque> // double ended queue

int main()
{
    std::deque<int> myDQ = { 1, 2, 3, 4, 5};
    // adding to the queue
    myDQ.push_back(6); // we can add to the back
    myDQ.push_front(0); // we can add to the front

    // remove from back or front
    myDQ.pop_front();
    myDQ.pop_back();

    // printing the queue we give us the original queue
    // we can iterate through a deque
    for (auto& item : myDQ)
    {
        std::cout << item << '\n';
    }
}