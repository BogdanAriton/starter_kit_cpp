#include <iostream>
#include <unordered_map>
#include <chrono>

// with buffer for the values
using hashTable = std::unordered_map<int, uint64_t>;

uint64_t fibonacci(int no, hashTable& myMap)
{
    if (no == 0) return 0;
    if (no == 1) return 1;
    
    myMap.insert({0,0});
    myMap.insert({1,1});
    int start = 2;

    while (start <= no)
    {
        myMap.insert({start, myMap[start-1] + myMap[start-2]});
        start++;
    }

    return myMap[no];
}

int main(int argc, const char*[] )
{
    volatile int value = 50;
    hashTable myMap(value);
    auto start = std::chrono::steady_clock::now();
    std::cout << "fibonacci of " << value << " = " << fibonacci(value, myMap) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << "time elapsed = " << duration.count() << " sec" << '\n'; 
}