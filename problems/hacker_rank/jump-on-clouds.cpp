// https://www.hackerrank.com/challenges/jumping-on-the-clouds/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup
#include <bits/stdc++.h>
using namespace std;

int jumpingOnClouds(vector<int> c) {
    int jumps = 0;
    if (c[0] == 1 && c[1] == 1) return 0; // we start with an impossilbe jump
    
    size_t end = c.size() - 2;
    int start = 0;
    for (int i =0; i < c.size(); ++i)
    {
        if (c[i] == 0)
        {
            start = i;
            break;
        }
    }
    int pos = start;
    cout << end << '\n';
    while (pos <= end)
    {
        if (c[pos+1] == 1)
            pos += 2;
        else if (c[pos+1] == 0 && c[pos+2] == 0 )
            pos += 2;
        else if (c[pos+1] == 0 && c[pos+2] == 1 )
            pos +=1;
        else
            pos +=1;

        jumps += 1;
    }
    return jumps;
}

int main()
{
    vector<int> c = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
                //    0  1  2  3  4   5  6  7  8  9  10
    cout << jumpingOnClouds(c) << '\n';
}