#include <iostream>
#include <unordered_map>

// with buffer for the values
using hashTable = std::unordered_map<int, uint64_t>;
hashTable myMap(45);

uint64_t fibonacciRecursive(int start, int no)
{
    if (start == no) 
    {
        myMap.insert({no, myMap[no-1] + myMap[no-2]});
        return myMap[no];
    }

    myMap.insert({start, myMap[start-1] + myMap[start-2]});
    return fibonacciRecursive(start+1, no);
}

uint64_t fibonacci(int no)
{
    if (no == 0) return 0;
    if (no == 1) return 1;

    return fibonacciRecursive(2, no);
}

int main(int argc, const char*[] )
{
    myMap.insert({0,0});
    myMap.insert({1,1});
    std::cout << fibonacci(45) << '\n';
}