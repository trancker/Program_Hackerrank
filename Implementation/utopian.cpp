#include <bits/stdc++.h>

using namespace std;

int fast_exp(int base, int exp) {
    int res = 1;
    while (exp > 0) {
       if (exp % 2 == 1) res = (res * base);
       base = (base * base);
       exp /= 2;
    }
    return res;
}

int main() {
    int t;
    int n, i;
    cin >> t;
    for (i = 0; i< t; i++) {
        cin >> n;
        cout << fast_exp(2, (n + 1) / 2 + 1) - 1 - (n % 2) << endl;
    }
    return 0;
}
