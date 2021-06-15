#include "number.h"
#include <math.h>
using namespace sections;

auto numbers::words(const uint64_t& num) -> std::string
{
    // determine the size of num
    // can't use size_of since
    sizeof(num);
    return std::string();
}

auto numbers::getDigit(int digit) -> std::string
{
    switch (digit)
    {
        case static_cast<int>(Digits::one): return "zero"; break;
        case static_cast<int>(Digits::two): return "one"; break;
        case static_cast<int>(Digits::three): return "two"; break;
        case static_cast<int>(Digits::four): return "three"; break;
        case static_cast<int>(Digits::five): return "four"; break;
        case static_cast<int>(Digits::six): return "five"; break;
        case static_cast<int>(Digits::seven): return "six"; break;
        case static_cast<int>(Digits::eight): return "seven"; break;
        case static_cast<int>(Digits::nine): return "eight"; break;
    }
}

auto numbers::getTeens(int digit) -> std::string
{
    switch (digit)
    {
        case static_cast<int>(Teens::eleven): return "eleven"; break;
        case static_cast<int>(Teens::twelve): return "twelve"; break;
        case static_cast<int>(Teens::thirteen): return "thirteen"; break;
        case static_cast<int>(Teens::fourteen): return "fourteen"; break;
        case static_cast<int>(Teens::fiveteen): return "fiveteen"; break;
        case static_cast<int>(Teens::sixteen): return "sixteen"; break;
        case static_cast<int>(Teens::seventeen): return "seventeen"; break;
        case static_cast<int>(Teens::eightten): return "eightten"; break;
        case static_cast<int>(Teens::nineteen): return "nineteen"; break;
    }
}

auto numbers::getTens(int no) -> std::string
{
    switch (no)
    {
        case static_cast<int>(Tens::ten): return "ten"; break;
        case static_cast<int>(Tens::twenty): return "twenty"; break;
        case static_cast<int>(Tens::thirty): return "thirty"; break;
        case static_cast<int>(Tens::forty): return "forty"; break;
        case static_cast<int>(Tens::fifty): return "fifty"; break;
        case static_cast<int>(Tens::sixty): return "sixty"; break;
        case static_cast<int>(Tens::seventy): return "seventy"; break;
        case static_cast<int>(Tens::eighty): return "eighty"; break;
        case static_cast<int>(Tens::nighty): return "nighty"; break;
    }
}