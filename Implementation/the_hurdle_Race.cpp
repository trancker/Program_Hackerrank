#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, k;
    cin >> n >> k;
    assert(n > 0 && n <= 100);
    assert(k > 0 && k <= 100);
    int mx = 0;
    while(n -- ){
        int x; cin >> x;
        assert(x > 0 && x <= 100);
        mx = max(mx, x);    
    }
    cout << max(0, mx - k) << "\n";
    return 0;
}
