#include <iostream>
#include <algorithm>
#include <numeric>

struct MyCollection
{
    int a = 0;
    std::string b{};
};

int main()
{
    using namespace std;
    int a[10] = { 1, 3, 4, 6, 3, 4, 4, 5, 6 , 6 };

    // Using begin(<colletion>) works with C style arrays like we have here :)
/*     std::count       */
    auto result = std::count(std::begin(a), std::end(a), 6);


    MyCollection coll[5] = { {1, "test1"}, {6, "test2"}, {2, "test2"}, {3, "test3"}, {2, "test2"}};
    // let's count 2s
    result = std::count_if(std::begin(coll), std::end(coll), [](const auto& item){
        return (item.a == 2 && item.b == "test2");
    });

    std::cout << result << '\n';

/* any_of, none_of, all_of */
    auto ones = std::any_of(begin(coll), end(coll), [](auto& elem){
        return elem.a == 1;
    });

    std::cout << ones << '\n';

    auto sameOnes = std::all_of(begin(coll), end(coll), [](auto& elem){
        return elem.a == 1;
    });

    std::cout << sameOnes << '\n';

    auto noOnes = std::none_of(begin(coll), end(coll),[](auto& elem){
        return elem.a == 1;
    });

    std::cout << noOnes << '\n';
/* enumerate and accumulate
*/
    int total = accumulate(begin(a), end(a), 0, [](int x, int i){ return i < 6; });
    //std::cout << "accumulate total =" << total << '\n';

    std::string words[] = {"word1", "word2", "word3"};
    string twords = accumulate(begin(words), end(words), string("words are ="), 
    [](const string& total, const string& i) { return total + " " + i;});

    cout << twords << '\n';
}