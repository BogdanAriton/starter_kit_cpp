#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Solution
{
    bool isSameLength(const std::string &a, const std::string &b)
    {
        return a.size() == b.size();
    };

    bool haveSameLetter(const std::string &a, const std::string &b)
    {
        for (auto char_a : a)
        {
            auto countInB = std::count(begin(b), end(b), char_a);
            if (countInB == 0) return false;
            else
            {
                auto countInA = std::count(begin(a), end(a), char_a);
                if (countInB != countInA) return false;
            }
        }
        return true;
    };

public:
    // we need to group string that have the same letters
    // the first check is the size of the string
    // then for each letter of the current string we can check if it's part of the other
    // if it's not then it's not the same anagram
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
    {
        std::vector<std::vector<std::string>> result;
        while (strs.size() > 0)
        {
            auto strlooper = strs.rbegin();
            // refresh iterator
            std::vector<std::string> group{};
            group.push_back(*strlooper);
            std::string tempStr(*strlooper);
            strs.pop_back();
            
            auto sub_looper = strs.begin();
            while (sub_looper != strs.end())
            {
                if (isSameLength(tempStr, *sub_looper) && haveSameLetter(tempStr, *sub_looper))
                {
                    group.push_back(*sub_looper);
                    sub_looper = strs.erase(sub_looper);
                }
                else
                {
                    sub_looper++;
                }
            }
            result.push_back(group);
        }
        
        return result;
    }
};

int main()
{
    std::vector<std::string> strs = {"ddddddddddg","dgggggggggg"};//{"eat", "tea", "tan", "ate", "nat", "bat"};
    // ["ddddddddddg","dgggggggggg"]
    Solution sol;
    auto result = sol.groupAnagrams(strs);
    for (auto& item : result)
    {
        for (auto subItem: item)
        {
            std::cout << subItem << '\n';
        }
        std::cout << '\n';
    }
}