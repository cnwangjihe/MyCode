#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3009,
		  INF  = 1000000009;

int f[MAXN][MAXN];
int cnt[MAXN];
int _head[MAXN],_node[MAXN*2],_next[MAXN*2],_val[MAXN*2];
int n,m,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
		for (int j=cnt[u];~j;j--)
			for (int k=cnt[v];k;k--)
				f[u][j+k]=max(f[u][j+k],f[u][j]+f[v][k]-_val[i]);
		cnt[u]+=cnt[v];
	}
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int k,a,v;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			f[i][j]=-INF;

	for (int i=1;i<=n-m;i++)
	{
		scanf("%d",&k);
		for (int j=0;j<k;j++)
		{
			scanf("%d%d",&a,&v);
			_connect(i,a,v);
			_connect(a,i,v);
		}
	}
	for (int i=n-m+1;i<=n;i++)
		scanf("%d",&f[i][1]),cnt[i]=1;
	dfs(1,0);
	for (int i=m;~i;i--)
		if (f[1][i]>=0)
			return printf("%d\n",i)&0;
	return 0;
}