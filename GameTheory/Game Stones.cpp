//Game Stones



#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int minMax(int n, bool firstPlayer, unordered_map<int, unordered_map<bool, int>>& cache){
    if(n < 2)
        return !firstPlayer;
    
    if(cache.find(n) != cache.end() && cache[n].find(firstPlayer) != cache[n].end())
        return cache[n][firstPlayer];
    
    int m1 = minMax(n - 2, !firstPlayer, cache);
    int m2 = minMax(n - 3, !firstPlayer, cache);
    int m3 = minMax(n - 5, !firstPlayer, cache);
    
    if(firstPlayer){
        cache[n][firstPlayer] = max(m1, max(m2, m3));
    } else {
        cache[n][firstPlayer] = min(m1, min(m2, m3));
    }

    return cache[n][firstPlayer];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        unordered_map<int, unordered_map<bool, int>> cache;
        cout << (minMax(n, true, cache) ? "First" : "Second") << endl;
    }
    return 0;
}