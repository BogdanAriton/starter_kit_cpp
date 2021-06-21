#include <iostream>
#include <vector>

bool findNumber(uint64_t number, uint64_t no) // this kind of bad if the number is really large
{
    if (number == no) return true;
    if (number < no) return false;
    uint64_t tempNo = no;
    while (number != 0) // O(n*m)
    {
        if (number % 10 == no % 10 && no != 0)
        {
            // found digit
            no /= 10;
        } 
        else
        {
            no = tempNo;
        }

        if (no == 0)
        {
            return true;
        }
        number /= 10;
    }
    return false;
};

// There might be other mathemetical ways that I'm not aware of right now

int main()
{
    uint64_t number = 32423532513412;

    std::vector<uint64_t> givenList = { 321, 4325345, 6345645, 32432, 324, 2353251, 3412, 32423532513412, 324235325134121, 3242353251341};
    for (auto& no : givenList) // O(k^3)
    {
        std::cout << "This number: " << no << (findNumber(number, no) ? " is in giveList" : " is not in givenList" ) << '\n';
    }
}

// std::cout << << '\n';