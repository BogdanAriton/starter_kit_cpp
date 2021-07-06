/*
Unordered containers
These containers maintain average constant-time complexity for search, insert, and remove operations. 
In order to achieve constant-time complexity, sacrifices order for speed by hashing elements into buckets. 

There are four unordered containers:
    unordered_set
    unordered_multiset
    unordered_map
    unordered_multimap
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>

// std::string cannot be used as constexpr so we will use a char array
constexpr char info_betty[] = R"(
{
    "name" : "betty",
    "age" : 6,
    "toys" : [
            "food", 
            "some_food", 
            "more_food"
            ]
}
)";
constexpr char info_paco[] = R"(
{
    "name" : "paco",
    "age" : 4,
    "toys" : [
            "elephant", 
            "marmot", 
            "fuk frog"
            ]
}
)";
constexpr char info_mox[] = R"(
{
    "name" : "mox",
    "age" : 7,
    "toys" : [
            "lopata", 
            "house", 
            "betty"
            ]
}
)";

/* will use this data structure to manage some fictional stuff */

struct place
{
    place(const std::string& place) noexcept : house(place) {};
    bool operator==(const place& other) const noexcept
    {
        return other.getPlace() == house;
    };
    std::string getPlace() const noexcept { return this->house; };
    operator std::string() const
    {
        return this->getPlace();
    }

private:
    std::string house{};
};

struct dog
{
    dog() = default;
    dog(const std::string &info) noexcept : info(info){};

    // we need to build equals operator so that the values can be compared
    bool operator==(const dog &other) const noexcept // this needs to be const because we have to promise we will not change the value when evaluating equality
    {
        //std::cout << "=== call to compare ===" << '\n';
        return other.getInfo() == info;
    }

    std::string getInfo() const noexcept { return this->info; };
    operator std::string() const
    {
        return this->getInfo();
    }

private:
    std::string info = {};
};

inline std::ostream& operator<<(std::ostream& os, const place& place)
{
    return os << std::string(place);
};

inline std::ostream& operator<<(std::ostream& os, const dog& dog)
{
    return os << std::string(dog);
};

template <typename T>
struct strHash
{
    // We use predfined hash functions of strings
    // and define our hash function as XOR of the
    // hash values.
    std::size_t operator()(const T& compare) const
    {
        //std::cout << "*** call to strHash ***" << '\n';
        return std::hash<std::string>()(compare);
    }
};

// template <typename T>
// struct OrderByPrice
// {
//     std::size_t operator<(const T &compare) const
//     {
//         std::cout << "*** call to strHash ***" << '\n';
//         return std::hash<double>()(compare);
//     }
// };

struct EntryData
{
    std::string timeStamp{};
    char action = '\0';
    std::string orderID{};
    char type = '\0';
    double price = 0;
    int size = 0;

    bool isEmpty() const noexcept
    {
        return timeStamp.empty() && (action == '\0') && orderID.empty();
    };
};

struct OrderKey
{
    std::string orderID{};
    double price = 0;
};

struct OrderComparator
{
    bool operator()(const OrderKey &lhs, const OrderKey &rhs) const noexcept
    {
        std::cout << "=== call to compare ===" << '\n';
        return lhs.price < rhs.price;
    }
};

int main()
{
    /*
    A set it's a list of things that don't repeat 
    */

    std::unordered_set<dog, strHash<dog>> my_dogs{dog(info_mox),
                                            dog(info_betty),
                                            dog(info_paco)};

    // for (auto &elem : my_dogs)
    //     std::cout << elem.getInfo() << " at bucket = " << my_dogs.bucket(elem) << '\n';


    std::unordered_multiset<dog, strHash<dog>> only_paco{dog(info_paco),dog(info_paco),dog(info_paco)};
    // for (auto &elem : only_paco)
    //     std::cout << elem.getInfo() << " at bucket = " << only_paco.bucket(elem) << '\n';

    std::unordered_map<place, dog, strHash<place>> mappedDog { std::make_pair<place, dog>(place("acasa"), dog(info_paco)),
                                                        std::make_pair<place, dog>(place("carpi"), dog(info_mox)),
                                                        std::make_pair<place, dog>(place("carpi"), dog(info_betty)) // betty will not be added becaue we already have a dog at carpi
                                                        };
    // for (auto &elem : mappedDog)
    //     std::cout << elem.first << elem.second << '\n';

    // to add betty we need to either:
    // 1: change the key from place to dog - this can be done easy given that the place and dog structure can use the same hash function and both implement equals
    // std::unordered_map<dog, place, strHash<dog>> mappedPlaces { std::make_pair<dog, place>(dog(info_paco), place("acasa")),
    //                                                     std::make_pair<dog, place>(dog(info_mox), place("carpi")),
    //                                                     std::make_pair<dog, place>(dog(info_betty), place("carpi")) // betty will not be added becaue we already have a dog at carpi
    //                                                     };
    // for (auto &elem : mappedPlaces)
    //     std::cout << elem.first << elem.second << '\n';
    // the above doesn't really make any sense because dogs should not be keys in general
    
    // or
    // 2: create a multimap - and we don't really have to change much because the pairs remain the same
    std::unordered_multimap<place, dog, strHash<place>> mappedDogs { std::make_pair<place, dog>(place("acasa"), dog(info_paco)),
                                                        std::make_pair<place, dog>(place("carpi"), dog(info_mox)),
                                                        std::make_pair<place, dog>(place("carpi"), dog(info_betty)) // betty will not be added becaue we already have a dog at carpi
                                                        };
    // for (auto &elem : mappedDogs)
    //     std::cout << elem.first << elem.second << '\n';

    EntryData elem1 = { "28800538", 'A', "b", 'S', 44.26, 100};
    OrderKey elem1key = {elem1.orderID, elem1.price};
    EntryData elem2 = { "28800562", 'A', "c", 'B', 44.10, 100};
    OrderKey elem2key = {elem2.orderID, elem2.price};
    EntryData elem3 = { "28800758", 'A', "d", 'B', 44.18, 157};
    OrderKey elem3key = {elem3.orderID, elem3.price};
    EntryData elem4 = { "28800758", 'A', "e", 'B', 44.10, 157};
    OrderKey elem4key = {elem4.orderID, elem4.price};

    std::multimap<OrderKey, EntryData, OrderComparator> orders;
    orders.insert({elem1key, elem1});
    orders.insert({elem2key, elem2});
    orders.insert({elem3key, elem3});
    orders.insert({elem4key, elem4});

    for (auto &elem : orders)
    {
         std::cout << elem.first.orderID << ' ' << elem.second.price << ' ' << elem.second.size << '\n';
    }
}
