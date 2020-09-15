//Running time of Algorithm



#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int insertionSortCount(vector <int>  ar) {
    int n = ar.size();
    int count=0;
    for(int i=1;i<n;i++){
        int curr = ar[i];
        for(int j=i-1;j>=0;j--){
            if(ar[j]>curr){
                ar[j+1]=ar[j];
                count++;
                if(j==0)
                    ar[j]=curr;
            }
            else{
                ar[j+1]=curr;
                j=-1;
            }
        }
    }
    return count;
}


/* Tail starts here */
int main() {
    vector <int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp); 
    }
    cout<<insertionSortCount(_ar);
    return 0;
}