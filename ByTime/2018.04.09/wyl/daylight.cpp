#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <stdio.h>

using namespace std;

const int MAXN = 200009*2,
		  MAXM = 200009*4;

struct TMax
{int v,i;};

int _head[MAXN],_next[MAXM],_node[MAXM];
TMax Max1[MAXN],Max2[MAXN];
int dfn[MAXN],low[MAXN],sta[MAXN],col[MAXN],fa[MAXN],c[MAXN];
bool vis[MAXN],_in[MAXN];
int st=0,cnt=0,cs=0,fp=0,n,m,ans,sum=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void tarjan(int u,int ff)
{
	_in[u]=1;
	int v;
	bool flag=1;
	vis[u]=1;sta[++st]=u;
	dfn[u]=low[u]=++cnt;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (ff==v && flag)
		{
			flag=0;
			continue;
		}
		if (!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else
		if (dfn[v]<dfn[u])
			low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u])
	{
		v=sta[st--];vis[v]=0;col[v]=++cs;
		for(;st && v!=u;v=sta[st--],vis[v]=false,col[v]=cs);
	}
}

int _find(int u)
{
	int x=u,tmp;
	while (u!=fa[u])
		u=fa[u];
	while (x!=fa[x])
	{
		tmp=fa[x];
		fa[x]=u;
		x=tmp;
	}
	return u;
}

void rebuild()
{
	int v,fv,fu;
	for (int u=1;u<=n;u++)
	{
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			fv=_find(col[v]),fu=_find(col[u]);
			if (col[v]==col[u] || fv==fu)
				continue;
			fa[fv]=fu;
			_connect(n+col[v],n+col[u]);
			_connect(n+col[u],n+col[v]);
		}
	}
	return ;
}

void dfs1(int u,int ff)
{
	_in[u]=1;
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==ff)
			continue;
		dfs1(v,u);
		c[u]++;
		if (Max1[u].v<Max1[v].v+c[v])
			Max2[u]=Max1[u],
			Max1[u].i=v,Max1[u].v=Max1[v].v+c[v];
		else
		if (Max2[u].v<Max1[v].v+c[v])
			Max2[u].i=v,Max2[u].v=Max1[v].v+c[v];
	}
	return ;
}

void dfs2(int u,int ff)
{
	_in[u]=1;
	if (Max1[ff].i!=u)
	{
		if (Max1[u].v<Max1[ff].v+c[ff])
			Max2[u]=Max1[u],
			Max1[u].i=ff,Max1[u].v=Max1[ff].v+c[ff];
		else
		if (Max2[u].v<Max1[ff].v+c[ff])
			Max2[u].i=ff,Max2[u].v=Max1[ff].v+c[ff];
	}
	else
	{
		if (Max1[u].v<Max2[ff].v+c[ff])
			Max2[u]=Max1[u],
			Max1[u].i=ff,Max1[u].v=Max2[ff].v+c[ff];
		else
		if (Max2[u].v<Max2[ff].v+c[ff])
			Max2[u].i=ff,Max2[u].v=Max2[ff].v+c[ff];
	}
	ans=max(ans,Max1[u].v+Max2[u].v+c[u]+1);
//	cerr << u << " : " << Max1[u].v << ' ' << Max2[u].v << " " << c[u] << '\n';
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==ff)
			continue;
		dfs2(v,u);
	}
}

int main()
{
	freopen("daylight.in","r",stdin);
	freopen("daylight.out","w",stdout);
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	int a,b;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	for (int i=1;i<=n;i++)
	{
		if (!_in[i])
			tarjan(i,0);
	}
	memset(_in,0,sizeof _in);
	rebuild();
	for (int i=1;i<=cs;i++)
		if (!_in[i+n])
			dfs1(n+i,0);
	memset(_in,0,sizeof _in);
	for (int i=1;i<=cs;i++)
		if (!_in[i+n])
		{
		//	cerr << "sdkfjhsdkfj";
			ans=0;
			dfs2(n+i,0);
			sum+=ans-1;
		}
	printf("%d\n",n-sum-1);
	return 0;
}