#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
    std::string name;
    Color color;
    Size size;
};

/* we will make use of the specification pattern */

template <typename T>
struct ISpecification
{
    // we should just use const because the specification should not change anything
    // we also return a const because we don't return a changable value
    virtual const bool is_satisfied(T* item) const = 0;
};

template <typename T>
struct AndSpec : ISpecification<T>
{
    // this idiom is called aggregation - because this container will now own the referenced object
    // thus the referenced object can change outside of this scope.
    // Just as a reminder - composition versus aggregation means that composition will take ownership of an object while aggregation will not
    const ISpecification<T>& first;
    const ISpecification<T>& second;

    AndSpec(const ISpecification<T>& first, const ISpecification<T>& second) : first(first), second(second) {};
    const bool is_satisfied(T* item) const override
    {
        return (first.is_satisfied(item) && second.is_satisfied(item));
    }
};

template <typename T> struct IFilter
{
    virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

struct  Filter : IFilter<Product>
{
    using Items = std::vector<Product*>;
    virtual Items filter(Items items, ISpecification<Product>& spec) override
    {
        Items result;
        for (auto& p: items)
        {
            if (spec.is_satisfied(p))
            {
                result.push_back(p);
            }
        }
        return result;
    }
};

struct ColorSpec : ISpecification<Product>
{
    Color color;
    explicit ColorSpec(Color color) : color(color) {};
    const bool is_satisfied(Product* item) const override
    {
        return item->color == color;
    }
};

struct SizeSpec : ISpecification<Product>
{
    Size size;
    explicit SizeSpec(Size size) : size(size) {};
    const bool is_satisfied(Product* item) const override
    {
        return item->size == size;
    }
};

int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product something{"something", Color::green, Size::medium};
    Product Car{"Car", Color::green, Size::large};
    Product SomethingElse{"Something else", Color::green, Size::small};
    Product house{"House", Color::blue, Size::large};

    std::vector<Product*> all{&apple, &tree, &house, &something, &SomethingElse, &Car};
    Filter filter;
    ColorSpec green(Color::green);
    auto get_green_things = filter.filter(all, green);

    std::for_each(begin(get_green_things), end(get_green_things), [](const Product* item){ std::cout << item->name << '\n'; });
    printf("\n");

    SizeSpec large(Size::large);
    AndSpec<Product> green_and_large(green, large);
    auto get_gLarge = filter.filter(all, green_and_large);

    std::for_each(begin(get_gLarge), end(get_gLarge), [](const Product* item){ std::cout << item->name << '\n'; });
    all.clear();
    return 0;
}

