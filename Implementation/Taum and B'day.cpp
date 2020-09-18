#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<cassert>

using namespace std;

#define ll long long int 
#define MOD7 2000000007
#define maxval MOD7-7

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        //input
        ll even, odd, even_price, odd_price, conversion_rate;
        cin >> even >> odd >> even_price >> odd_price >> conversion_rate;

        //calculations
        ll ans = (ll)MOD7*(ll)MOD7;
        ll as_it_is = even_price * even+odd_price * odd;
        ans = min(ans, as_it_is);
        ll price_all_even = odd_price * odd + even * (odd_price + conversion_rate);
        ll price_all_odd = even_price * even + odd * (even_price + conversion_rate);
        ans = min(ans, min(price_all_even, price_all_odd));

        // printing output
        cout << ans << endl;
    }
    return 0;
}
