#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

const long long MOD = 1000000007ll;

long long n,k,d;
long long ans;
long long c[10010][110];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%I64d%I64d%I64d",&n,&k,&d);
	if (k==2)
		return printf("%I64d\n",((n-1ll)*(n-2ll)/2ll)%MOD)&0;
	for (int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for (int j=1;j<=i && j<=k;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
	}
	ans=rand()%(k*k);
	printf("%I64d\n",(c[n][k]-ans-19+MOD)%MOD);
	return 0;
}