#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16,
		  MAXK = (1<<MAXN),
		  INF  = 2147483647;

int c[MAXK][MAXN],a[MAXN][MAXN];
int size[MAXK];
int n,ans;

void solve(int s,int u)
{
	if (s==0 || size[s]==1)
	{
		c[s][u]=0;
		return ;
	}
	int stat,ustat,vstat;
	for (int v=u+1;v<=n;v++)
	{
		if (u==v || !((1<<(v-1))&s))
				continue;
		stat=s-(1<<(v-1))-(1<<(u-1));
		for (int nstat=stat;;nstat=(nstat-1)&stat)
		{
			ustat=nstat+(1<<(u-1));
			vstat=(s-nstat)-(1<<(u-1));
			c[s][u]=min(c[s][u],c[ustat][u]+c[vstat][v]+(n-size[vstat])*size[vstat]*a[u][v]);
			c[s][v]=min(c[s][v],c[ustat][u]+c[vstat][v]+(n-size[ustat])*size[ustat]*a[u][v]);
			if (!nstat)
				break;
		}
	}
	return ;
}

int main()
{
//	freopen("2566.in","r",stdin);
//	freopen("2566.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
		for (int j=1;j<=n-i;j++)
			scanf("%d",&a[i][i+j]),a[i+j][i]=a[i][i+j];
	c[0][0]=0;
	for (int i=0;i<(1<<n);i++)
		for (int j=1;j<=n;j++)
			size[i]+=(((1<<(j-1))&i)!=0),c[i][j]=INF;

	for (int i=1;i<(1<<n);i++)
		for (int j=1;j<=n;j++)
			if ((1<<(j-1))&i)
				solve(i,j);
	ans=INF;
	for (int i=1;i<=n;i++)
		ans=min(ans,c[(1<<n)-1][i]);
	printf("%d\n",ans);
	return 0;
}