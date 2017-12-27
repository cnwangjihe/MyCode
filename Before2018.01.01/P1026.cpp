#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MOD = 1000000007,
		  HASH = 233,
		  MAXN = 302;
int n,k,s;
char ch[MAXN];
char f[9][MAXN],t[MAXN];
int ok[9],ll[9],map[MAXN][MAXN],dp[MAXN][MAXN];

int gethash(char c[])
{
    int le=strlen(c);
    int an=0;
    for(int i=0;i<le;i++)an=(an*HASH+c[i])%MOD;
    return an;
}
bool ha(int x,int y)
{
    for(int i=1;i<=s;i++)
	{
	    memset(t,0,sizeof(t));
	    strncpy( t, ch+x , min( ll[i] , y-x+1 ) );
	    if(gethash( t )==ok[i])return 1;
    }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) cin >> ch+(i*20-20);
    scanf("%d",&s);
    for(int i=1;i<=s;i++) cin >> f[i];
    for(int i=1;i<=s;i++) ll[i]=strlen(f[i]);
    for(int i=1;i<=s;i++) ok[i]=gethash( f[i] );
    int len=strlen(ch);
    for(int i=len-1;i>=0;i--)
	{
        for(int j=i;j>=0;j--)
		{
            map[j][i]+=map[j+1][i];
            if(ha(j,i)) map[j][i]++;
        }
    }

    for(int i=0;i<len;i++)
  		for(int j=1;j<=k;j++)
   	    	if(j==1)dp[i][j]=map[0][i];
   	    		else
   	         		for(int l=0;l<i;l++)
                		if(dp[l][j-1])
                			dp[i][j]=max(dp[i][j],dp[l][j-1]+map[l+1][i]);
    printf("%d\n",dp[len-1][k]);
    return 0;
}
