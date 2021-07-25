/*
The idea behind it is to have a more descriptive way of knowing what we are constructing

Factory Method:
    A function that creates objects.

Abstract Factory:
    It's abstract class the create an hierarchy of classes
*/
#include <iostream>
#include <memory>
#include <map>

struct HotDrink
{
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "this is a tea with volume = " << volume << '\n';
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "this is a coffee with volume = " << volume << '\n';
    }
};

// we need an abstract factory so that we can create many specific factories
struct HotDrinkFactory 
{
    virtual std::unique_ptr<HotDrink> make() = 0; 
};

struct CoffeeFactory : public HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() override
    {
        return std::make_unique<Coffee>();
    };
};

struct TeaFactory : public HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() override
    {
        return std::make_unique<Tea>();
    };
};

class DrinkFactory // we need it to do the mapping
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories;
public:
    DrinkFactory()
    {
        factories["coffee"] = std::make_unique<CoffeeFactory>();
        factories["tea"] = std::make_unique<TeaFactory>();
    }
    std::unique_ptr<HotDrink> make_drink(const std::string& name)
    {
        auto drink = factories[name]->make();
        return drink;
    }
};

// template magic - but this is not the pattern
// template <typename ParentType, typename ChildType>
// std::unique_ptr<ParentType> make_drink()
// {
//     return std::make_unique<ChildType>();
// }

int main()
{
    // auto t = make_drink<HotDrink, Tea>();
    // t->prepare(200);

    // auto c = make_drink<HotDrink, Coffee>();
    // c->prepare(200);

    DrinkFactory df;
    auto coffee = df.make_drink("coffee");
    coffee->prepare(100);

    auto tea = df.make_drink("tea");
    tea->prepare(200);
}