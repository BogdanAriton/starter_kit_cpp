#ifndef BOOK_ANALYZER_OUTPUT
#define BOOK_ANALYZER_OUTPUT

#include <string>
#include <iostream>
#include <algorithm>

enum class PrintAction
{
    print,
    dontPrint,
    printNA,
    printValue,
    trim
};

struct OutputData : public EntryData
{
    double value = 0;
    PrintAction action;
};

template <enum PrintAction>
struct Output{};

template <>
struct Output<PrintAction::trim>
{
    static std::string trimZeros(double value, int precision = 2)
    {
        std::string doubleToStr = std::to_string(value);
        auto at = std::find(begin(doubleToStr), end(doubleToStr), '.');
        int pos = distance(doubleToStr.begin(), at);
        doubleToStr = doubleToStr.substr(0, (pos+1) + precision);
        return doubleToStr;
    };
};

template <>
struct Output<PrintAction::dontPrint>
{
    static void print() {};
};

template <>
struct Output<PrintAction::printNA>
{
    static void print(const OutputData& outdata)
    {
        std::cout << outdata.timeStamp << ' '
                  << outdata.type << ' '
                  << "NA"
                  << '\n';
    }
};

template <>
struct Output<PrintAction::printValue>
{
    static void print(const OutputData& outdata)
    {
        std::cout << outdata.timeStamp << ' '
                  << outdata.type << ' '
                  << Output<PrintAction::trim>::trimZeros(outdata.value)
                  << '\n';
    }
};

template <>
struct Output<PrintAction::print>
{
    static void print(const OutputData& outdata)
    {
        if (outdata.action == PrintAction::dontPrint) Output<PrintAction::dontPrint>::print();
        if (outdata.action == PrintAction::printNA) Output<PrintAction::printNA>::print(outdata);
        if (outdata.action == PrintAction::printValue) Output<PrintAction::printValue>::print(outdata);
    }
};

#endif