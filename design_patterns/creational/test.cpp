#include <iostream>
#include <queue>
#include <memory>
#include <string>

struct entry
{
    virtual std::string print() const noexcept
    {
        return "I am parent";
    }
};

struct entryA : public entry
{
    std::string print() const noexcept override
    {
        return "I am entryA";
    }
};

struct entryB : public entry
{
    std::string print() const noexcept override
    {
        return "I am entryB";
    }
};

struct entryC : public entry
{
    std::string print() const noexcept override
    {
        return "I am entryC";
    }
};

// factory method
std::unique_ptr<entry> getEntry(int no)
{
    if (no == 1)
    {
        std::unique_ptr<entry> eA = std::make_unique<entryA>();
        return eA;
    }

    if (no == 2)
    {
        std::unique_ptr<entry> eB = std::make_unique<entryB>();
        return eB;
    }
    if (no == 3)
    {
        std::unique_ptr<entry> eC = std::make_unique<entryC>();
        return eC;
    }
};

/* 

!!!!!!! This is stupid !!!!!!
Don't do this!

struct Process
{
    static void printing(const std::unique_ptr<entry> &entry)
    {
        if (typeid(decltype(*(entry.get()))) == typeid(entryA))
        {
            showEntryA(std::move(entry));
        }

        if (typeid(decltype(*(entry.get()))) == typeid(entryB))
        {
            showEntryB(std::move(entry));
        }

        if (typeid(decltype(*(entry.get()))) == typeid(entryC))
        {
            showEntryC(std::move(entry));
        }
    };

    static void showEntryA(const std::unique_ptr<entry>& entry)
    {
        std::cout << entry->print() << '\n';
    }

    static void showEntryB(const std::unique_ptr<entry>& entry)
    {
        std::cout << entry->print() << '\n';
    }

    static void showEntryC(const std::unique_ptr<entry>& entry)
    {
        std::cout << entry->print() << '\n';
    }
};
*/

void printing(const std::unique_ptr<entry>& entry)
{
    std::cout << entry->print() << '\n';
};

int main()
{
    std::queue<std::unique_ptr<entry>> testQ;

    testQ.push(getEntry(1));
    testQ.push(getEntry(2));
    testQ.push(getEntry(3));

    while (!testQ.empty())
    {
        std::unique_ptr<entry> item = std::move(testQ.front());
        printing(item);
        testQ.pop();
    }
}
