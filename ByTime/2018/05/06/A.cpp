#pragma comment(linker, "/STACK:102400000,102400000") 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 500009,
		  MAXM = 500009*2;

int t[MAXN*4];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2],pos[MAXN];
int top[MAXN],val[MAXN],w[MAXN],fa[MAXN],rw[MAXN],dep[MAXN],siz[MAXN],son[MAXN];
int n,m,tim=0,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u]=val[rw[l]];
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	t[u]=t[u*2]^t[u*2+1];
	return ;
}

void _update(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u]=v;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_update(u*2,l,mid,p,v);
	else
		_update(u*2+1,mid+1,r,p,v);
	t[u]=t[u*2]^t[u*2+1];
	return ;
}

int _ask(int u,int l,int r,int al,int ar)
{
	if (al>ar)
		return 0;
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)/2,ans=0;
	if (al<=mid)
		ans^=_ask(u*2,l,mid,al,ar);
	if (ar>mid)
		ans^=_ask(u*2+1,mid+1,r,al,ar);
	return ans;
}

void dfs1(int u,int fat)
{
	int v;
	dep[u]=dep[fat]+1;
	fa[u]=fat;
	siz[u]=1;
	son[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		dfs1(v,u);
		if (siz[son[u]]<siz[v])
			son[u]=v;
		siz[u]+=siz[v];
	}
	return ;
}

void dfs2(int u,int topp)
{
	int v;
	w[u]=++tim;
	top[u]=topp;
	if (son[u])
		dfs2(son[u],topp);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u] || v==son[u])
			continue;
		dfs2(v,v);
	}
	return ;
}

int ask(int x,int y)
{
	int ans=0;
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans^=_ask(1,1,n,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if (dep[y]<dep[x])
		swap(x,y);
	return ans^_ask(1,1,n,w[x],w[y]);
}

void update(int x,int y)
{
	_update(1,1,n,w[x],y);
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int a,b,c;
	char s[100];
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);
	for (int i=1;i<=n;i++)
		rw[w[i]]=i;
	_build(1,1,n);
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%s",s);
		scanf("%d%d",&a,&b);
		if (s[0]=='Q')
			printf("%s\n",ask(a,b)==0?"No":"Yes");
		else
			update(a,b);
	}
	return 0;
}