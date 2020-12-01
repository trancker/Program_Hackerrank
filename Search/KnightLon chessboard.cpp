//This program is designed by Mohammad Tanzil Idrisi uder the construction of CodeXEater


#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define se second
int n;

int func(int a, int b) {

    int visited[100][100];
    memset(visited,0,sizeof(visited));
    queue<pair<pair<int,int>,int> > q;
    q.push(mp(mp(0,0),0));
    while(!q.empty()) {
	pair<pair<int,int>,int> p = q.front();
	q.pop();
	int x = p.fr.fr;
	int y = p.fr.se;
	if(x>=n || y>=n) continue;
	if(x==n-1 && y==n-1) {
	    return p.se;
	}
	int c = p.se;
	if(!visited[x+a][y+b]) {
	    q.push(mp(mp(x+a,y+b),c+1));
	    visited[x+a][y+b] = 1;
	}
	if(y-b>=0 && !visited[x+a][y-b]) {
	    q.push(mp(mp(x+a,y-b),c+1));
	    visited[x+a][y-b] = 1;
	}
	if(x-a>=0 && !visited[x-a][y+b]) {
	    q.push(mp(mp(x-a,y+b),c+1));
	    visited[x-a][y+b] = 1;
	}
	if(x-a>=0 && y-b>=0 && !visited[x-a][y-b]) {
	    q.push(mp(mp(x-a,y-b),c+1));
	    visited[x-a][y-b] = 1;
	}
	swap(a,b);
	if(!visited[x+a][y+b]) {
	    q.push(mp(mp(x+a,y+b),c+1));
	    visited[x+a][y+b] = 1;
	}
	if(y-b>=0 && !visited[x+a][y-b]) {
	    q.push(mp(mp(x+a,y-b),c+1));
	    visited[x+a][y-b] = 1;
	}
	if(x-a>=0 && !visited[x-a][y+b]) {
	    q.push(mp(mp(x-a,y+b),c+1));
	    visited[x-a][y+b] = 1;
	}
	if(x-a>=0 && y-b>=0 && !visited[x-a][y-b]) {
	    q.push(mp(mp(x-a,y-b),c+1));
	    visited[x-a][y-b] = 1;
	}
    }
    return -1;
}

int main() {

    cin>>n;

    for(int i=1;i<n;i++) {
	for(int j=1;j<n;j++) {

	    int ans = func(i,j);
	    cout<<ans<<" ";

	}
	cout<<endl;
    }

}
