//Leena sort



#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef pair<string,string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

#ifdef TESTING
  #define DEBUG fprintf(stderr,"====TESTING====\n")
  #define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define DEBUG 
  #define VALUE(x)
  #define debug(...)
#endif

#define FOR(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define FORN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define FORD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define FORSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define FORC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define FOREACH(a,b) for (auto &(a) : (b))
#define REP(i,n) FOR(i,0,n)
#define REPN(i,n) FORN(i,1,n)
#define MAX(a,b) a = max(a,b)
#define MIN(a,b) a = min(a,b)
#define SQR(x) ((LL)(x) * (x))
#define RESET(a,b) memset(a,b,sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define TC(t) while(t--)

inline string IntToString(LL a){
  char x[100];
  sprintf(x,"%lld",a); string s = x;
  return s;
}

inline LL StringToInt(string a){
  char x[100]; LL res;
  strcpy(x,a.c_str()); sscanf(x,"%lld",&res);
  return res;
}

inline string GetString(void){
  char x[1000005];
  scanf("%s",x); string s = x;
  return s;
}

inline string uppercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
  return s;
}

inline string lowercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return s;
}

inline void OPEN (string s) {
  #ifndef TESTING
  freopen ((s + ".in").c_str (), "r", stdin);
  freopen ((s + ".out").c_str (), "w", stdout);
  #endif
}

//end of jonathanirvings' template v3.0.3 (BETA)

int q;
pair<LL,LL> batas[100005];
int l;
LL c;

bool valid(LL x, int k)
{
  return batas[k].fi <= x && x <= batas[k].se;
}

void solve(int st, int sz, LL rem)
{
  rem -= (sz - 1);
  // debug("\n>>>>%d %d %lld\n",st,sz,rem);
  if (sz == 0) return;
  FORN(i,1,sz)
  {
    int a = i - 1;
    int b = sz - 1 - a;
    // debug("%d %d %d %lld\n",i,a,b,rem-batas[a].fi);
    if (valid(rem - batas[a].fi, b))
    {
      printf("%d ", st + i - 1);
      solve(st, a, batas[a].fi);
      solve(st + a + 1, b, rem - batas[a].fi);
      return;
    } else if (valid(rem - batas[a].se, b))
    {
      printf("%d ", st + i - 1);
      solve(st, a, batas[a].se);
      solve(st + a + 1, b, rem - batas[a].se);
      return;
    }
  }
}

int main()
{
  batas[0] = mp(0,0);
  batas[1] = mp(0,0);
  FORN(i,2,100000)
  {
    int a = (i - 1) / 2;
    int b = (i - 1) - a;
    batas[i].se = (i - 1) + batas[i-1].se;
    batas[i].fi = (i - 1) + batas[a].fi + batas[b].fi;
  }
  // FORN(i,1,10) debug("%d %d\n",batas[i].fi,batas[i].se);
  scanf("%d",&q);
  TC(q)
  {
    scanf("%d %lld",&l,&c);
    if (c < batas[l].fi || c > batas[l].se)
    {
      puts("-1");
      continue;
    }
    solve(1, l,c);
    puts("");
  }
  return 0;
}








