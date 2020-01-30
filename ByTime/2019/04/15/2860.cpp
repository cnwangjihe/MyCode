// Date      : 2019-04-15 11:46:01
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 59,
		  MAXM = MAXN*MAXN;
int sum,n;
int a[MAXN];
long double p[MAXN],f[2][MAXM][MAXM];
long double ans;

int main()
{
	freopen("2860.in","r",stdin);
	freopen("2860.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		int v;
		memset(f,0,sizeof f);
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=1;i<=n;i++)
			scanf("%d",&v),p[i]=(long double)v/100.0;
		f[0][0][0]=1;
		sum=0;
		int now=0,last,t;
		for (int i=1;i<=n;i++)
		{
			now^=1,last=now^1;
			memset(f[now],0,sizeof f[now]);
			for (int j=0;j<=sum;j++)
				for (int k=0;k<=sum;k++)
				{
					if (!f[last][j][k])
						continue;
					t=j+a[i];
					if (j+a[i]>k)
						f[now][t][t]+=f[last][j][k]*(1.0-p[i]);
					else
						f[now][t][k]+=f[last][j][k]*(1.0-p[i]);
					if (j-a[i]>-1)
						f[now][j-a[i]][k]+=f[last][j][k]*p[i];
					else
						f[now][0][k]+=f[last][j][k]*p[i];
				}
			sum+=a[i];
		}
		ans=0;
		for (int i=0;i<=sum;i++)
			for (int j=0;j<=sum;j++)
				ans+=f[now][i][j]*j;
		printf("%.8Lf\n",ans);
	}
	return 0;
}