#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stack>
using namespace std;
#define REP(I,N)   FOR(I,0,N)
#define pb push_back
#define LL long long
LL limit=500000;
int main()
{
    int a,x,b,y;
    cin>>a>>x>>b>>y;
    a+=x;
    b+=y;
    if(a==b)
        cout<<"YES"<<endl;
    else
    {
        int d=0;
        for(;;a+=x,b+=y)
        {
            if(a==b)
            {
                d=1;
                break;
            }
           else if(a > b && x>=y)
                break;
           else if(b>a && y>=x)
                break;
        }
        if(d)
          cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;

    }
    return 0;
}
