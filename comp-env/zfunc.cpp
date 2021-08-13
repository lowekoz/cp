#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

// linear longest matching prefix starting from position i
// applications: patterns serach <pattern>$<text> n number of distinct substrings in string.
// https://cp-algorithms.com/string/z-function.html#toc-tgt-1
vector<int> z_function(string str) {
    int n = (int)str.length();
    vector<int> z(n);
    // [l,r] (inclusive) is Z-box, storing the rightmost prefix match >0 starting from position i
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        // since s[0..r-l] == s[l..r], if i <= r, we may reuse z[i-l] knowledge as long as r - i + 1 ([i,r]) >= z[i-l]
        // i.e. if z[i-l] continues outside r, we cannot use it completely. See last position i=6 for "aaaabaa"
        // [l,r] = [5,6] but z[i-l] = z[6-5] = z[1] = 3 cannot be correct. In that case
        // we take distance r-i+1 ([i,r]) and do trivial search from here to serach right of r (unknown territory)
        if (i <= r) {
            if (z[i-l] <= r - i + 1) {
                z[i] = z[i-l];
            }
            else {
                z[i] = r - i + 1;
            }
        }

        // trivial serach
        while (i + z[i] < n && str[z[i]] == str[i + z[i]])
            ++z[i];

        //if found new prefix match update l and r.
        if (i + z[i] - 1 > r) // z[i] similar including position i, means i+0,í+1...,i+z[i]-1
            l = i, r = i + z[i] - 1;
    }
    return z;
}