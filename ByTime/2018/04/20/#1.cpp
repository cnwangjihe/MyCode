#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const long long MOD = 1000000007ll;

long long n,k,d;
long long ans;
long long f[20][10010],c[10010][110];
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
	f[0][0]=1;
	for (int i=0;i<16;i++)
		for (int j=0;j<=n-k;j++)
			for (int w=0;(1ll<<i)*(d+1)*w<=j && (d+1)*w<=k/2;w++)
				f[i+1][j]=(f[i+1][j]+f[i][j-(1ll<<i)*w*(d+1)]*c[k/2][(d+1)*w])%MOD;
	for (int i=0;i<=n-k;i++)
		ans=(ans+f[16][i]*c[n-i-k/2][k/2])%MOD;
	printf("%I64d\n",(c[n][k]-ans+MOD)%MOD);
	return 0;
}