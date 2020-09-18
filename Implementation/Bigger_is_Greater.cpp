#include <bits/stdc++.h>
using namespace std;

int main(){
    int test;
    cin >> test;
    while(test--) {
        string inp;
        cin >> inp;
        if (next_permutation(inp.begin(), inp.end()) == false ) {
            cout << "no answer" << endl;
        }
        else {
            cout << inp << endl;
        }
    }
    return 0;
}
