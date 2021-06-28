#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
const char letter = 'a';

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    long repeat = 0;
    std::for_each(s.begin(), s.end(), 
        [&](char c) {
            (c == letter) ? repeat += 1 : repeat;
        });

    repeat = (n / s.length()) * repeat;
    size_t noRemaining = n - (s.length() * (n / s.length()));
    for (int i = 0; i < noRemaining; i++)
    {
        if (s[i] == letter)
            repeat += 1;
    }

    return repeat;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = repeatedString(s, n);

    cout << result << "\n"; //fout

    fout.close();

    return 0;
}
