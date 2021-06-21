/*
We will see now how a simple queue can be worked with.
In a queue normal operations will be to push in the back and pop from the front
*/

#include <iostream>
#include <queue>

int main()
{
    std::queue<int> myQ; // we cannot use an initializer list to constrcut the queue
    
    myQ.push(1);
    myQ.push(2);
    myQ.push(3);
    myQ.push(4);
    myQ.push(5);
    myQ.push(6);
    myQ.push(7);
    myQ.push(8);
    myQ.push(9);
    myQ.push(10);

    while (!myQ.empty())
    {
        // we will print the elements in order
        std::cout << myQ.front() << '\n';
        myQ.pop();
    }
}