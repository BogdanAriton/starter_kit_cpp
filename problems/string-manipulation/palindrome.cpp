#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

/*
    Check if a string is palindrom
    But the catch is that we should check if there is a palindrom in a string

    This can be done with stack because we add a char in a stack one by one and if we find again we pop it out
    for example:
         this will be a palindrom: 
            t1: aaaabaaaa
            t2: ciwbaabbaacacuwekkeekkewucacaabbaabw
            t3: wbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwci

*/


bool isPalindrom(const std::string& str, int i, int j)
{
    // a a a b a a a
    // a a b b a a 
    // i = 0 , j = 5
    while (i < j)
    {
        if (str[i] == str[j])
        {
            i++;
            j--;
        }
        else
        {
            return false;
        }
    }
    return true;
}
auto countPalindroms(const std::string& str) -> int
{
    // std::vector<std::string> result{};
    int result = 0;
    int checks = 0;
    int j = str.size()-1;
    while (j > 0)
    {
        int i = 0;
        while (i <= j)
        {
            // if we want palindromes that are greater than a given length
            // we can specify it here:
            if ((j-i+1) >= 2)
            {
                if (isPalindrom(str, i, j))
                {
                    //std::cout << str.substr(i, j-i+1) << '\n';
                    result++;
                }
                checks++;
            }
            i++;
        }
        j--;
    }
    return result;
}

using namespace std;
int find_palindromes_in_sub_string(const string& input, int i, int j) {
  int count = 0;
  for (; i >= 0 && j < input.length(); --i, ++j) {
    if (input[i] != input[j]) {      
      break;
    } 
    ++count;
  }
  return count;
}

int find_all_palindrome_substrings(const string& input) {
  int count = 0;
  for (int i = 0; i < input.length(); ++i) {    
    count += find_palindromes_in_sub_string(input, i - 1, i + 1);
    count += find_palindromes_in_sub_string(input, i, i + 1);
  }
  return count;
}

int main()
{
    //std::string str = "wbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwci";
    std::string str = "wbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwciwbaabbaacacuwekkeekkewucacaabbaabwci";
    //std::string str = "ciwbaabbaacacuwekkeekkewucacaabbaabw";


    auto start = std::chrono::steady_clock::now();
    auto result = find_all_palindrome_substrings(str);//countPalindroms(str);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = end-start;
    //std::cout << "10801 chars to search through." << '\n';
    std::cout << "Number of palindroms found = " << result << " - time elapsed: " << dur.count() << " seconds" << '\n';
}


// Note: multithreading 
// Creating separate thread for parsing the string doesn't make things faster necessarily - because the cost of macking the thread is greater
// std::vector<std::string> result{};
// std::mutex resultGuarded;
//                 std::thread checker = std::thread([=]()
//                                                   {
//                                                       std::string substr = str.substr(i, j - i);
//                                                       //std::cout << "checking = " << substr << '\n';
//                                                       if (isPalindrom(substr))
//                                                       {
//                                                           std::scoped_lock<std::mutex> lock(resultGuarded);
//                                                           result.push_back(substr);
//                                                       }
//                                                   });
//                 checker.detach();