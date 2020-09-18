#include<iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;

int main(){
    int t = 26;
    vector<int> h(t);
    
    for (int i = 0; i < t; i++) {
        cin >> h[i];
    }
        
    string s;
    cin >> s;

    int rect_height = 0;

    for (int j = 0; j < s.length(); j ++) {
        rect_height = max(rect_height, h[s[j] - 'a']);
    }
        
    int ans = rect_height * 1 * s.length();
    cout << ans << endl;

    return 0;
}
