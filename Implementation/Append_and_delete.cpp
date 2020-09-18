#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())

int main() {
    #ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
    #endif
    string s, t;
    int k;
    cin >> s >> t >> k;
    int p = 0;
    while (p < min(sz(s), sz(t)) && s[p] == t[p])
        ++p;
    int vmin;
    if (k % 2 == (sz(s) + sz(t)) % 2)
        vmin = sz(s) + sz(t) - 2 * p;
    else
        vmin = sz(s) + sz(t) + 1;
    if (k < vmin)
        cout << "No\n";
    else
        cout << "Yes\n";
}
