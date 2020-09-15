//Hackerland Radio Transmitters


#include <bits/stdc++.h>

using namespace std;

int a[100000+2];
int main(){

    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    { 
        cin>>a[i]; 
    }
  
    sort(a+1,a+n+1);
    int ans = 0, i=1;
    while(i<=n)
    {
        int maxijabe = a[i] + m;
        int j=i;
        ans = ans + 1;
        while(j<=n and a[j]<=maxijabe){
            i = j;
            j++;
        }
        
        maxijabe = a[i]+m;
        j = i;
        while(j<=n and a[j]<=maxijabe){
            i = j;
            j++;
        }
        i = i + 1;
    }
    cout<<ans<<endl;

    return 0;
}