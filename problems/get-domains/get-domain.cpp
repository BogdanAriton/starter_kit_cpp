/*
You are in charge of a display advertising program. Your ads are displayed on websites all over the internet. You have some CSV input data that counts how many times that users have clicked on an ad on each individual domain. Every line consists of a click count and a domain name, like this:

counts = [ "900,google.com",
     "60,mail.yahoo.com",
     "10,mobile.sports.yahoo.com",
     "40,sports.yahoo.com",
     "300,yahoo.com",
     "10,stackoverflow.com",
     "20,overflow.com",
     "5,com.com",
     "2,en.wikipedia.org",
     "1,m.wikipedia.org",
     "1,mobile.sports",
     "1,google.co.uk"]

Write a function that takes this input as a parameter and returns a data structure containing the number of clicks that were recorded on each domain AND each subdomain under it. For example, a click on "mail.yahoo.com" counts toward the totals for "mail.yahoo.com", "yahoo.com", and "com". (Subdomains are added to the left of their parent domain. So "mail" and "mail.yahoo" are not valid domains. Note that "mobile.sports" appears as a separate domain near the bottom of the input.)

Sample output (in any order/format):

calculateClicksByDomain(counts) =>
com:                     1345
google.com:              900
stackoverflow.com:       10
overflow.com:            20
yahoo.com:               410
mail.yahoo.com:          60
mobile.sports.yahoo.com: 10
sports.yahoo.com:        50
com.com:                 5
org:                     3
wikipedia.org:           3
en.wikipedia.org:        2
m.wikipedia.org:         1
mobile.sports:           1
sports:                  1
uk:                      1
co.uk:                   1
google.co.uk:            1

n: number of domains in the input
(individual domains and subdomains have a constant upper length)

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

using map =  std::unordered_map<string, int>;
auto calculateClicksByDomain(const vector<pair<int, string>>& counts) -> map
{
  unordered_map<string, int> result{}; // this will contain all of the domains and subdomains with their sum
  
  // cycle through the vector will take the right side and will strip that
  // find(begin, end, [](char ch){}{
  //  return ch == '.';
  //}) -> position as an iterator of the string
  // std::distance(begin, it);
  // std:: - substring(position, chars);
  
  for (auto& item : counts)
  {
      if (result.find(item.second) != result.end())
      {
          result[item.second] += item.first;
      }
      else
        result.insert(pair(item.second, item.first));
      // 10,mobile.sports.yahoo.com
      
      string subdomains = item.second;
      auto posItr = find(subdomains.begin(), subdomains.end(), '.');
      while (posItr != subdomains.end())
      {
        //std::cout << *posItr << '\n';
        int pos = distance(subdomains.begin(), posItr);    
        string subdomain = subdomains.substr(pos + 1, subdomains.size() - pos);
        //std::cout << subdomain << '\n';
        
        if (result.find(subdomain) != result.end())
        {
            result[subdomain]+= item.first;
        }
        else
          result.insert(pair(subdomain, item.first));
        
        subdomains = subdomain;
        posItr = find(subdomains.begin(), subdomains.end(), '.');
        //std::cout << *posItr << '\n';
      }
      
  }
  return result;
}

int main() {
  
  vector<pair<int, string>> counts = {
    {900,"google.com"},
    {60,"mail.yahoo.com"}, 
    {10,"mobile.sports.yahoo.com"},
    {40,"sports.yahoo.com"},
    {300,"yahoo.com"},
    {10,"stackoverflow.com"},
    {20,"overflow.com"},
    {5,"com.com"},
    {2,"en.wikipedia.org"},
    {1,"m.wikipedia.org"},
    {1,"mobile.sports"},
    {1,"google.co.uk"}
  };
  

  //std::cout << subdomains << '\n';
  
  for (auto& item : calculateClicksByDomain(counts))
  {
    std::cout << item.first << " " << item.second  << '\n';
  }
  
  return 0;
}