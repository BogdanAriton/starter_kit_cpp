/*
    v = [1 3 1 3 1 4 1 3 2 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5]
         a b c d e f g h i j k l m n o p q r s t u v w z y z
    v contains the hight for each letter in the alfabet
    word = a low letter word that has no more than 10 letters
    the width is 1mm
    we need the number of letters x width x height of the tallest letter
    ex: zaba = 5, 1, 3, 1 => 4 letters => tallest is z = 7 => 4l x 1mm x 7mm = 28mm2

*/
#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> mapLetterToHeights(const vector<int>& heights)
{
    unordered_map<char, int> letterHeights{};
    int i = 97;
    int j = 0;
    while (i <= 122)
    {
        letterHeights.emplace(pair(i, heights[j]));
        i++;
        j++;
    }
    return letterHeights;
}

int designerPdfViewer(vector<int> h, string word)
{
    // map letters to heights:
    unordered_map<char, int> letterHeights = mapLetterToHeights(h);
    unsigned int maxHeight = 0;
    for (auto& ch : word)
    {
        if (maxHeight < letterHeights[ch]) maxHeight = letterHeights[ch];
    }
    return word.size() * (1 * maxHeight);
}

int main()
{
    vector<int> v = {1, 3, 1, 3, 1, 4, 1, 3, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    string word = "abc";
    cout << designerPdfViewer(v, word) << '\n';
}