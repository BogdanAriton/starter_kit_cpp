#include <memory>
#include <iostream>
#include <algorithm>
#include <forward_list>
#include <string>
#include <array>
#include <ranges>
#include <tuple>
#include <utility>

using _string = std::string;

template <typename T>
class Animals
{
    using _fList = std::forward_list<T>;
    using _values = std::initializer_list<T>;
private:
    _string name = {};
    _fList itemList = {};

public:
    Animals(const _string& name, const _values& args) noexcept : name(name), itemList(args) { std::cout << "Animals is constructed" << '\n'; };
    virtual ~Animals() { std::cout << "Animals is destructed" << '\n'; };//= default;
    virtual _fList getToys() const = 0;
    virtual _string getName() const = 0;
    virtual void setToys(const _values& toys) = 0;

    Animals(const Animals&) = delete;
    Animals& operator=(const Animals&) = delete;
    Animals(Animals&&) = delete;
    Animals& operator=(Animals&&) = delete;
};

template <typename T>
class Dog: public Animals<T>
{
    using _fList = std::forward_list<T>;
    using _values = std::initializer_list<T>;
public:
    Dog(const _string& name, const _values& toys) noexcept : Animals<T>(name, toys), name(name), toys(toys) { std::cout << "Dog is constructed" << '\n'; };
    _fList getToys() const override { return toys; }
    _string getName() const override { return name; };
    void setToys(const _values& toys) { this->toys = toys; };
    ~Dog() { std::cout << "Dog is destructed" << '\n'; };

private:
    _string name = {};
    _fList toys = {};
};

template <typename First, typename... Args>
void printToys(const First& first, Args&&... args)
{
    constexpr std::size_t size = sizeof...(Args);
    for (const auto&item : first.getToys())
    {
        std::cout << item << '\n';
    }

    if constexpr (size > 0)
    {
        return printToys(args...);
    }
}

int main()
{
    // simple example using unique_pointers
    using data = std::unique_ptr<int>;
    std::forward_list<data> simple_list = { };

    simple_list.push_front(std::make_unique<int>(1));
    simple_list.push_front(std::make_unique<int>(2));
    simple_list.push_front(std::make_unique<int>(3));

    for (const auto& item : simple_list)
    {
        std::cout << *item << '\n';
    }

    // a more complex approach using inheritance and paramter packs
    // Animals and Dog keep their toys in a forward list initialized using initializer list
    std::unique_ptr<Animals<_string>> roger = std::make_unique<Dog<_string>>( "roger", std::initializer_list<_string>({ "fuk frog" , "elephant" , "marmot"}));
    Dog<int> tom("tom", {1, 2, 3, 4, 5});
    Dog<float> igor("igor", { 1.3f, 2.5f, 3.8f, 4.223f, 5.321f});
    printToys(*roger, tom, igor);
}
