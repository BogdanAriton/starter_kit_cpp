// https://www.hackerrank.com/challenges/attribute-parser/problem
/*
Sample input:
10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size

expected output:
    tag_one
    val_907
    Not Found!
    Not Found!
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
string getTagName(const string&);
unordered_map<string, string> getAttrNames(const string&);
unordered_map<string, string> getTagsAttrValue(int);
vector<string> getQueryLines(int);

int main()
{
    string input_html_lines_no_queries;
    getline(cin, input_html_lines_no_queries);
    vector<string> lines = split(rtrim(input_html_lines_no_queries));
    if (lines.size() > 2)
    {
        cout << "to many argument, please enter numer of line in html and number of lines in queries, ex: 4 3" << '\n';
        return 0;
    }
    auto tags = getTagsAttrValue(stoi(ltrim(rtrim(lines[0]))));
    auto queryLines = getQueryLines(stoi(ltrim(rtrim(lines[1]))));

    for (auto &qLine : queryLines)
    {
        if (tags.find(qLine) != tags.end())
            cout << tags[qLine] << '\n';
        else
            cout << "Not Found!" << '\n';
    }
}

unordered_map<string, string> getTagsAttrValue(int htmlLinesCount)
{
    unordered_map<string, string> tags{};
    stack<string> tagNames;
    string nestedTags = "";
    for (int i = 0; i < htmlLinesCount; ++i)
    {
        string htmlLine;
        getline(cin, htmlLine);
        htmlLine = ltrim(rtrim(htmlLine));
        // </
        if (htmlLine[0] == '<' && htmlLine[1] == '/')
        {
            // this is a closing tag
            string closingTagName = htmlLine.substr(2, htmlLine.size() - 3);
            if (closingTagName == tagNames.top())
            {
                string topTab = tagNames.top();
                tagNames.pop();
                if (tagNames.empty()) nestedTags = "";
                else
                {
                    nestedTags = nestedTags.substr(0, nestedTags.size() - (topTab.size() + 1));
                }
            }
            continue;
        }
        // < tag1 value = "HelloWorld"> 
        string tagName = getTagName(htmlLine);
        if (tagNames.empty())
            nestedTags = tagName;
        else
            nestedTags = nestedTags + "." + tagName;

        tagNames.push(tagName);
        auto attrs = getAttrNames(htmlLine);
        if (attrs.size() == 0) continue;
        for (auto& att : attrs)
        {
            tags[nestedTags + "~" + att.first] = att.second;
        }
    }

    return tags;
}



vector<string> getQueryLines(int queryLinesCount)
{
    vector<string> queryLines = {};
    for (int i = 0; i < queryLinesCount; ++i)
    {
        string queryLine;
        getline(cin, queryLine);
        queryLine = ltrim(rtrim(queryLine));
        queryLines.push_back(queryLine);
    }
    return queryLines;
}

string getTagName(const string& str)
{
    auto firstTag = str.find('<');
    string tagLine = ltrim(str.substr(firstTag + 1, str.size() - (firstTag + 1)));
    auto firstSpace = tagLine.find(' ');
    if (firstSpace == std::string::npos)
    {
        firstSpace = tagLine.find('>');
    }
    return rtrim(ltrim(tagLine.substr(0, firstSpace)));
}

unordered_map<string, string> getAttrNames(const string& str)
{
    unordered_map<string, string> attrValue = {};

    auto firstTag = str.find('<');
    string tagLine = ltrim(str.substr(firstTag + 1, str.size() - (firstTag + 1)));
    auto firstSpace = tagLine.find(' ');
    string attributeLine = str.substr(firstSpace + 1, tagLine.size() - (firstSpace + 1));

    while (attributeLine.find('=') != std::string::npos)
    {
        auto firstEq = attributeLine.find('=');
        string attr = ltrim(rtrim(attributeLine.substr(0, firstEq)));
        auto firstComma = attributeLine.find('\"');
        string valueLine = attributeLine.substr(firstComma + 1, attributeLine.size() - (firstComma + 1));
        firstComma = valueLine.find('\"');
        string value = valueLine.substr(0, firstComma);
        attrValue.emplace(attr, value);
        attributeLine = valueLine.substr(firstComma+1, valueLine.size() - (firstComma+1));
    }

    return attrValue;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}