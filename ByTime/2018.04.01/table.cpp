#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 109;

int n,m,lim,ans;
int mp[MAXN][MAXN];
int f[(1<<10)][MAXN];

int getcost(int k,int p)
{
	int sum=0;
	for(int i=1;i<=m;i++)
	{
		if((k&1)!=mp[p][i])
			sum++;
		k>>=1;
	}
	return sum;
}

int main()
{
	freopen("2434.in","r",stdin);
	freopen("2434.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		ans=0x7fffffff;
		scanf("%d%d%d",&n,&m,&lim);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				scanf("%d",&mp[i][j]);
		if(n<m)
		{
			for(int i=1;i<=n;i++)
				for(int j=i;j<=m;j++)
					swap(mp[i][j],mp[j][i]);
			swap(n,m);
		}
		if(m<=lim)
		{
			int k;
			for(int j=0;j<(1<<m);j++)
				f[1][j]=getcost(j,1);
			for(int i=2;i<=n;i++)
				for(int j=0;j<(1<<m);j++)
				{
					k=j^((1<<m)-1);
					f[i][j]=min(f[i-1][j],f[i-1][k])+getcost(j,i);
				}
			for (int j=0;j<(1<<m);j++)
				ans=min(ans,f[n][j]);
			printf("%d\n",ans>lim?-1:ans);
			continue;
		}
		int t,sum;
		for (int i=1;i<=n;i++)
		{
			sum=0;
			for (int j=1;j<=n;j++)
			{
				t=0;
				for (int k=1;k<=m;k++)
					if (mp[i][k]!=mp[j][k])
						t++;
				sum+=min(t,m-t);
			}
			ans=min(ans,sum);
		}
		printf("%d\n",ans>lim?-1:ans);
	}
	return 0;
}