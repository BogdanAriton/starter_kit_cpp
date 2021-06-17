#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main()
{
    std::vector<int> myVec = { 2, 54, 44, 65767, 22, 1, 2, 33, 3 };
    // for an int array int arr[] = { 1, 2, 3, 5, 6, 7, 8, 4};
    // we can determine the size by deviding the size of the list by the size of the element
    // int size = sizeof(arr) / sizeof(arr[0])

    for (auto& item : myVec)
    {
        std::cout << item << "  ";
    }
    std::cout << '\n';

    std::sort(myVec.begin(), myVec.end(), [](const int& item1, const int& item2){
        return item1 > item2;
    });
    for (auto& item : myVec)
    {
        std::cout << item << "  ";
    }
    std::cout << '\n';
}
