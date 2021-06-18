/*
Blocks =
[
    {
        "school" : false,
        "gym" :  true,
        "store" : false
    },
    {
        "school" : true,
        "gym" :  false,
        "store" : false
    },
    {
        "school" : true,
        "gym" :  false,
        "store" : false
    },
    {
        "school" : false,
        "gym" :  false,
        "store" : false
    },
    {
        "school" : false,
        "gym" :  true,
        "store" : false
    },
    {
        "school" : false,
        "gym" :  false,
        "store" : true
    },
]

Input = ["school", "store", "gym"]
Output = Block[?]
In this example: block: 4 - with distances = 2, 0, 1
    {
        "school" : false,
        "gym" :  true,
        "store" : false
    },
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

void printVec(const std::vector<std::vector<int>>& vec)
{
    for (auto& items : vec)
    {
        for (auto& item : items)
        {
            std::cout << " " << item;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<std::unordered_map<int, bool>> transform(const std::vector<std::unordered_map<std::string, bool>>& blocks, const std::vector<std::string>& requirements)
{
    std::vector<std::unordered_map<int, bool>> intBlocks(blocks.size(), std::unordered_map<int, bool>(requirements.size()));
    int i = 0; // this is the index for the vector of vectors
    int j = 0; // this is the index for each vector
    for (const auto& items : blocks)
    {
        for (auto &item : items)
        {
            auto pos = std::find(requirements.begin(), requirements.end(), item.first);
            if (pos != requirements.end())
            {
                size_t at = std::distance(requirements.begin(), pos);
                intBlocks[i].emplace(at, item.second);
            }
        }
        i++;
    }

    return intBlocks;
}

int main()
{
    // we first build out input here
    // will be a vector of unordered_maps
    std::vector<std::unordered_map<std::string, bool>> strBlocks =
        {
            {{"school", false}, {"gym", true}, {"store", false}},
            {{"school", true}, {"gym", false}, {"store", false}},
            {{"school", true}, {"gym", true}, {"store", false}},
            {{"school", false}, {"gym", true}, {"store", false}},
            {{"school", false}, {"gym", true}, {"store", false}},
            {{"school", false}, {"gym", true}, {"store", false}},
            {{"school", false}, {"gym", true}, {"store", true}}};

    std::vector<std::string> requirements = { "school", "store" };
    // have to create a new structure that has these values in order so that we can iterate safely through them
    auto blocks = transform(strBlocks, requirements);
    // we can then build a vector that hold distances for each item in the map
    // so the vector size will be the same as our blocks vector and each element in the vector can represent each appartment
    // we go through each item in the vector (initialized with -1 for example) and add values based on distances
    std::vector<std::vector<int>> app_distances(blocks.size(), std::vector<int>(blocks[0].size()+1, -1));

    // this will be the postion we store the max element in for each appartment
    int maxPos = app_distances[0].size() - 1;

    int i = 0;
    for (auto& item : blocks[i])
    {
        if (item.second == true)
        {
            app_distances[0][i] = 0;
        }
        i++;
    }

    // I'm iterating thorugh each block
    for (int i = 1; i < app_distances.size(); ++i)
    {
        // for each block I want to update the distance to school, gym and store
        int j = 0;
        for (auto& item : blocks[i])
        {
            if (item.second == true)
            {
                app_distances[i][j] = 0;
            }
            else if (app_distances[i - 1][j] != -1)
            {
                app_distances[i][0] = app_distances[i - 1][j] + 1;
            }
            j++;
        }
    }

    // will go backward through the blocks
    for (int i = app_distances.size() - 2; i >= 0; --i)
    {
        for (int j = 0; j < maxPos; ++j)
        {
            if (app_distances[i][j] == -1)
            {
                if (app_distances[i+1][j] != -1)
                {
                    app_distances[i][j] = app_distances[i+1][j] + 1;
                }
            }
        }
        app_distances[i][maxPos] = *std::max_element(app_distances[i].begin(), app_distances[i].end()-1);
    }
    app_distances[0][maxPos] = *std::max_element(app_distances[0].begin(), app_distances[0].end()-1);
    int last = app_distances.size()-1;
    app_distances[last][maxPos] = *std::max_element(app_distances[last].begin(), app_distances[last].end()-1);
    

    int min = app_distances[0][maxPos];
    int index = -1;
    for (int i = 0; i < app_distances.size(); ++i)
    {
        if (app_distances[i][maxPos] < min)
        {
            min = app_distances[i][maxPos];
            index = i;
        }
    }

    printVec(app_distances);

    std::cout << "Best appartmenet found at index: " << index << '\n';
    for ( auto& item : blocks[index])
    {
        std::cout << "   " << requirements[item.first] << " : " << (item.second == true? "true" : "false") << '\n';
    }
}