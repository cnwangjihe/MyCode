#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 309,
		  MAXV = 255;
const long long INF = 1e17;

long long x[MAXN],y[MAXN],c[MAXN];
long long f[MAXN][MAXN],cost[MAXN][MAXN];
int n,k;
long long ans=INF;

int main()
{
	freopen("2441.in","r",stdin);
	freopen("2441.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++)
	{
		scanf("%lld%lld",&x[i],&y[i]);
		c[x[i]]=y[i];
	}
	long long tmp;
	for (int i=0;i<MAXV;i++)
		for (int j=i+1;j<=MAXV;j++)
			for (int p=i+1;p<j;p++)
			{
				tmp=min((long long)p-i,(long long)j-p);
				cost[i][j]+=(c[p]*(long long)tmp*tmp);
			}
	for (int i=0;i<=MAXV;i++)
		for (int j=0;j<i;j++)
			f[i][1]+=(c[j]*(long long)(i-j)*(long long)(i-j));
	for (int j=2;j<=k;j++)
		for (int i=j-1;i<=MAXV;i++)
		{
			f[i][j]=INF;
			for (int p=j-2;p<i;p++)
				f[i][j]=min(f[i][j],f[p][j-1]+cost[p][i]);
		}
	
	for (int i=k-1;i<=MAXV;i++)
	{
		for (int j=i+1;j<=MAXV;j++)
			f[i][k]+=( c[j]*(long long)(j-i)*(long long)(j-i) );
		ans=min(ans,f[i][k]);
	}
	printf("%lld\n",ans);
	return 0;
}