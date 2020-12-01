//This program is developed by Mohammad Tanzil Idrisi under the construction of CodeXEAter

#include <bits/stdc++.h>

using namespace std;

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define pb push_back
#define mp make_pair
#define pd(x) printf("%d", x)
#define pdn(x) printf("%d\n", x)
#define plld(x) printf("%I64d", x)
#define plldn(x) printf("%I64d\n", x)
#define fi first
#define se second
#define sd(x) scanf("%d",&x)
#define sd2(x,y) scanf("%d%d",&x,&y);
#define sd3(x,y,z) scanf("%d%d%d",&x,&y,&z); //spaces should not be there to avoid tle
#define slld(x) scanf("%I64d",&x)
#define LET(x, a)  __typeof(a) x(a)
#define foreach(it, v) for(LET(it, v.begin()); it != v.end(); it++)
#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)

template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;

/*
ifstream fin("input.txt");
ofstream fout("output.txt");
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
*/

const int N = 200100;

int n;
ll p[N];

int main()
{
	FASTER;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> p[i];
	}	
	
	set<ll> s;
	s.insert(p[0]);
	
	ll mx = -1e18;
	
	for(int i = 1; i < n; i++){
		auto it = s.upper_bound(p[i]);
		if(it == s.end()){
			s.insert(p[i]);
			continue;
		}
		
		mx = max(mx, p[i] - (*it));
		s.insert(p[i]);
	}
	
	cout << -mx;	
	
	return 0;
}
