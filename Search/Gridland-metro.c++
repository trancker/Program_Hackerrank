//This code is edited and written by Mohammad Tanzil Idrisi


#include <bits/stdc++.h>
#include<assert.h>

using namespace std;

vector<pair<int, int> >v[1003];
map<int,int>mp;

void solution() {

    int n, m, k, r, c1, c2, sz1, sz2;
    long long ans, temp, non_emp;

    cin>>n>>m>>k;

    for(int i=0; i<k; i++){
        cin>>r>>c1>>c2;
        assert(r>0 && r<=n && c1>0 && c1<=m && c2>=c1 && c2<=m);

        if(mp.find(r) == mp.end())
            mp[r] = mp.size();
        r = mp[r];

        v[r].push_back( make_pair(c1,c2) );
    }


    sz1 = mp.size();
    for(int i=1; i<=sz1; i++)
        sort(v[i].begin(), v[i].end());

    ans = (long long)n*(long long)m;
    non_emp = 0;

    for(int i=1,p; i<=sz1; i++)
    {
        sz2 = v[i].size();
        p = 0;
        for(int j=0; j<sz2; j++)
        {
            if(v[i][j].first <= p)
            {
                temp = v[i][j].second - p;
                if(temp>0)
                    non_emp += temp;
            }
            else if(v[i][j].first > p)
                non_emp += (v[i][j].second - v[i][j].first + 1);

            p = max(p, v[i][j].second);
        }
    }

    ans -= non_emp;
    assert(ans>=0);
    cout<<ans<<"\n";
}

int main () {

    solution();

    return 0;
}
