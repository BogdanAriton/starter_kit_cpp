// the scope is to get back the numbers in letters
// first we get digits = 1 - 9
// then we get tens
// then hundreds
// then thousands
// then tens of thousands
// then hundres of thousands
// then millions .. and so on

#ifndef MY_NUMS
#define MY_NUMS

#include <cstdint>
#include <string>

namespace sections
{
    enum class Digits : int
    {
        one = 1,
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        nine = 9
    };

    enum class Teens : int
    {
        eleven = 11,
        twelve = 12,
        thirteen = 13,
        fourteen = 14,
        fiveteen = 15,
        sixteen = 16,
        seventeen = 17,
        eightten = 18,
        nineteen = 19
    };

    enum class Tens : int
    {
        ten = 10,
        twenty = 20,
        thirty = 30,
        forty = 40,
        fifty = 50,
        sixty = 60,
        seventy = 70,
        eighty = 80,
        nighty = 90
    };

    enum class Hundred : int
    {
        hundred = 100
    };

    enum class Thousands : int
    {
        thousand = 1000
    };

    enum class Millions : unsigned long long
    {
        million = 1000000000
    };

    enum class Billions : unsigned long long
    {
        billion = 1000000000000
    };

    enum class Trillions : unsigned long long
    {
        trillion = 1000000000000000
    };
};

class numbers
{
    uint64_t number;

    std::string getDigit(int);
    std::string getTeens(int);
    std::string getTens(int);
    std::string getHundred(uint64_t);
    std::string getThousands(uint64_t);
    std::string getMillions(uint64_t);
    std::string getBillions(uint64_t);
    std::string getTrillions(uint64_t);

public:
    numbers( uint64_t number): number(number) {};
    std::string words(const uint64_t&);
};

#endif // MY_NUMS