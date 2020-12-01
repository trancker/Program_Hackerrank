//This program is developed by MOhammad Tanzil under the construction of CodeXEater

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long long n,m,temp;
    cin>>n;
    vector<int> a;
    for(long long i=0;i<n;i++) {
        cin >> temp;
        a.push_back(temp);
    }
    cin>>m;
    vector<int> b;
    for(long long i=0;i<m;i++){
        cin >> temp;
        b.push_back(temp);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    long long i=0,j=0;
    while(i<n && j<m){
        if(a[i]==b[j]) {
            i++;j++;
            b[j-1]=0;
        }
        else if(a[i]>b[j])j++;
        else i++;
    }
    set<int> st;
    for(i=0;i<m;i++) {
        if(b[i]!=0) st.insert(b[i]);
    }
    for(set<int>::iterator it = st.begin();it!=st.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    return 0;
}
