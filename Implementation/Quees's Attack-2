#include <bits/stdc++.h>
using namespace std;

#define IN(a,x,y) (a>=x && a<=y)

const int MAXOBS = 100000;

int N, K;
int ox[MAXOBS+10], oy[MAXOBS+10];

int val(int x, int y)
{
    int i;

    int d11,d12,d21,d22,r1,r2,c1,c2;

    d11 = min( x-1, y-1 );
    d12 = min( N-x, N-y );
    d21 = min( N-x, y-1 );
    d22 = min( x-1, N-y );

    r1 = y-1;
    r2 = N-y;
    c1 = x-1;
    c2 = N-x;
    for(i=0; i<K; i++)
    {
        if( x>ox[i] && y>oy[i] && x-ox[i] == y-oy[i] ) d11 = min( d11, x-ox[i]-1 );
        if( ox[i]>x && oy[i]>y && ox[i]-x == oy[i]-y ) d12 = min( d12, ox[i]-x-1 );
        if( ox[i]>x && y>oy[i] && ox[i]-x == y-oy[i] ) d21 = min( d21, ox[i]-x-1 );
        if( x>ox[i] && oy[i]>y && x-ox[i] == oy[i]-y ) d22 = min( d22, x-ox[i]-1 );

        if( x == ox[i] && oy[i]<y ) r1 = min( r1, y-oy[i]-1 );
        if( x == ox[i] && oy[i]>y ) r2 = min( r2, oy[i]-y-1 );
        if( y == oy[i] && ox[i]<x ) c1 = min( c1, x-ox[i]-1 );
        if( y == oy[i] && ox[i]>x ) c2 = min( c2, ox[i]-x-1 );
    }

    return d11 + d12 + d21 + d22 + r1 + r2 + c1 + c2;
}
int main(void)
{
    int i,j,k,kase=0;

    int x,y;
    scanf("%d %d",&N, &K);
    scanf("%d %d",&x, &y);

    assert(IN(N,1,100000));
    assert(IN(K,0,100000));

    for(i=0; i<K; i++)
    {
        scanf("%d %d",&ox[i], &oy[i]);
        assert(IN(ox[i],1,N) && IN(oy[i],1,N) && (ox[i]!=x || oy[i]!=y));
    }

    printf("%d\n",val(x, y));
    return 0;
}
