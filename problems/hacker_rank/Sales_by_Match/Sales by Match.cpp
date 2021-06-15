/*
There is a large pile of socks that must be paired by color. Given an array of integers representing the color of each sock, determine how many pairs of socks with matching colors there are.

Example

There is one pair of color and one of color . There are three odd socks left, one of each color. The number of pairs is

.Function Description

Complete the sockMerchant function in the editor below.

sockMerchant has the following parameter(s):

    int n: the number of socks in the pile
    int ar[n]: the colors of each sock

Returns

    int: the number of pairs

Input Format

The first line contains an integer, the number of socks represented in .
The second line contains space-separated integers,the colors of the socks in the pile.

Constraints

where

Sample Input

STDIN                       Function
-----                       --------
9                           n = 9
10 20 20 10 10 30 50 10 20  ar = [10, 20, 20, 10, 10, 30, 50, 10, 20]

Sample Output

3

*/
#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// Complete the sockMerchant function below.
int sockMerchant(int n, std::vector<int> ar) {

	std::vector<int> pairs;
	auto it = ar.begin();
	int noOfPairs = 0;
	for (;it != ar.end(); ++it)
	{
		auto offset = it;
		auto found = 0;
		while ((offset = std::find(offset, ar.end(), *it)) != ar.end() && 
			(std::find(pairs.begin(), pairs.end(), *it) == pairs.end()))
		{
			found++;
			offset++;
		}
		if (found > 1)
		{
			pairs.push_back(*it);
			noOfPairs = noOfPairs + found/2;
		}
	}
	return noOfPairs;
}

int main()
{
	int n = 9;
	std::string str = "10 20 20 10 10 30 50 10 20";
	std::string::iterator strItr = std::unique(str.begin(), str.end(), 
		[](const char& x, const char& y) 
		{
			return x == y && x == ' ';
		});

	// we trim the string
	str.erase(strItr, str.end());
	while (str[str.length() - 1] == ' ')
	{
		str.pop_back();
	}

	std::vector<std::string> splits;
	splits.reserve(n);
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = str.find(delimiter);

	while (pos != std::string::npos)
	{
		splits.emplace_back(str.substr(i, pos - i));
		i = pos + 1;
		pos = str.find(delimiter, i);
	}
	splits.emplace_back(str.substr(i, std::min(pos, str.length() - i + 1)));

	std::vector<int> ar(n);

	for (int i = 0; i < n; i++) {
		int ar_item = stoi(splits[i]);

		ar[i] = ar_item;
	}

	int result = sockMerchant(n, ar);

	std::cout << result << std::endl;
}
