#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MAXK = 21;

int vl[MAXN],sum[MAXN],dep[MAXN];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int val[MAXN][MAXK],fa[MAXN][MAXK];
int n,m,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int dfs1(int u)
{
	int v;
	dep[u]=dep[fa[u][0]]+1;
	sum[u]=vl[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u][0])
			continue;
		fa[v][0]=u;
		sum[u]+=dfs1(v);
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u][0])
			continue;
		val[v][0]=sum[u]-sum[v];
	}
	return sum[u];
}

void dfs2(int u)
{
	int v;
	for (int i=1;fa[u][i-1]!=0;i++)
	{
		fa[u][i]=fa[fa[u][i-1]][i-1];
		val[u][i]=max(val[u][i-1],val[fa[u][i-1]][i-1]);
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u][0])
			continue;
		dfs2(v);
	}
	return ;
}

int LCA(int x,int y)
{
	if (dep[x]<dep[y])
		swap(x,y);
	int ans=sum[x];
	int d=dep[x]-dep[y];
	for (int i=0;d;i++)
		if ((1<<i)&d)
		{
			d-=(1<<i);
			ans=max(ans,val[x][i]);
			x=fa[x][i];
		}
	if (x==y)
		return ans;
	ans=max(ans,sum[y]);
	for (int i=19;~i;i--)
		if (fa[x][i]!=fa[y][i])
		{
			ans=max(ans,max(val[x][i],val[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	ans=max(ans,sum[fa[x][0]]-sum[x]-sum[y]);
	return ans;
}
int main()
{
	freopen("2645.in","r",stdin);
	freopen("2645.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&vl[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
	}
	dfs1(1);
	dfs2(1);/*
	for (int i=1;i<=n;i++)
		printf("%d %d\n",sum[i],val[i][0]);*/
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
	return 0;
}