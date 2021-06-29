// https://www.hackerrank.com/challenges/counting-valleys/submissions/code/220948764?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'countingValleys' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER steps
 *  2. STRING path
 */

int countingValleys(int steps, string path) {
    vector<vector<char>> valeys = {};
    vector<char> valey = {};
    int sealevel = 0;
    int level = 0;
    
    unordered_map<char, int> septType = { {'D', -1} , {'U', 1}};
    
    for (auto& step : path)
    {
        level += septType[step];
        if (level < sealevel)
        {
            
            valey.push_back(step);
        }
        if (level == sealevel)
        {
            // reached sealevel
            if (valey.size() > 0)
            {
                valeys.push_back(valey);
                valey.clear();
            }            
        }
    }
    
    return valeys.size();  
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string steps_temp;
    getline(cin, steps_temp);

    int steps = stoi(ltrim(rtrim(steps_temp)));

    string path;
    getline(cin, path);

    int result = countingValleys(steps, path);

    fout << result << "\n";

    fout.close();

    return 0;
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
