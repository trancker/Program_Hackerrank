#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
    #endif
    int n;
    cin >> n;
    int p[100];
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    int ans[100];
    for (int i = 1; i <= n; ++i)
        ans[p[p[i]]] = i;
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << '\n';
}
