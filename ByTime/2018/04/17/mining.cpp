#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 209,
		  MAXM = MAXN*2,
		  INF  = 2000000009;

int _next[MAXM],_node[MAXM],_head[MAXN];
int f[MAXN][MAXN],cost[MAXN][MAXN],d[MAXN];
int n,k,ans=INF,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void calc(int u,int root,int fa,int sum)
{
	int v;
	cost[u][root]=d[sum];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		calc(v,root,u,sum+1);
	}
	return ;
}

void dfs(int u,int fa)
{
	int v,t;
	for (int i=1;i<=n;i++)
		f[u][i]=cost[u][i];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
		t=INF;
		for(int j=1;j<=n;j++)
			t=min(t,f[v][j]);
		for(int j=1;j<=n;j++)
			f[u][j]+=min(t+k,f[v][j]);
	}
	return ;
}

int main()
{
	freopen("mining.in","r",stdin);
	freopen("mining.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int a,b;
	scanf("%d%d",&n,&k);
	for (int i=1;i<n;i++)
		scanf("%d",&d[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	for (int i=1;i<=n;i++)
		calc(i,i,0,0);
	dfs(1,0);
	for (int i=1;i<=n;i++)
		ans=min(f[1][i],ans);
	printf("%d\n",ans+k);
	return 0;
}