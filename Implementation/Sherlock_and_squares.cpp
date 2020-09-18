#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

int main() {
    int t;
    cin >> t;
    while(t--) {
        long long int a, b, ans = 0, i;
        cin >> a >> b;
        for(i=1; ; i++) {
            if (i * i > b) break;
            if (i * i <= b && i * i >= a) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
