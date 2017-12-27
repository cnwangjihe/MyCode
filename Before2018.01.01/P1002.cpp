#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

const int MAXN = 25;

long long a,b,n,m;
long long l[MAXN][MAXN],mp[MAXN][MAXN];

using namespace std;

int main()
{
    scanf("%lld%lld%lld%lld",&n,&m,&a,&b);
    mp[a][b]=1;
    mp[a-1][b-2]=1;
    mp[a-1][b+2]=1;
    mp[a+1][b-2]=1;
    mp[a-2][b-1]=1;
    mp[a+2][b-1]=1;
    mp[a-2][b+1]=1;
    mp[a+2][b+1]=1;
    mp[a+1][b+2]=1;
    l[1][0]=1;
    for(int i=1;i<=n+1;++i)
        for(int j=1;j<=m+1;++j)
        {
            l[i][j]=l[i-1][j]+l[i][j-1];
            if(mp[i-1][j-1]) l[i][j]=0;
        }
    printf("%lld\n",l[n+1][m+1]);
    return 0;
}
