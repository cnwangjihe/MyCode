#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009,
		  MAXM = 300009;

int t[MAXN*4];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2],_val[MAXN*2],pos[MAXN];
int top[MAXN],val[MAXN],w[MAXN],fa[MAXN],rw[MAXN],dep[MAXN],siz[MAXN],son[MAXN];
int n,tim=0,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
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
	t[u]=max(t[u*2],t[u*2+1]);
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
	t[u]=max(t[u*2],t[u*2+1]);
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
		ans=max(ans,_ask(u*2,l,mid,al,ar));
	if (ar>mid)
		ans=max(ans,_ask(u*2+1,mid+1,r,al,ar));
	return ans;
}

void dfs1(int u,int fat,int va)
{
	int v;
	val[u]=_val[va];
	pos[va/2+1]=u;
	dep[u]=dep[fat]+1;
	fa[u]=fat;
	siz[u]=1;
	son[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		dfs1(v,u,i);
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
		ans=max(ans,_ask(1,1,n,w[top[x]],w[x]));
		x=fa[top[x]];
	}
	if (dep[y]<dep[x])
		swap(x,y);
	return max(ans,_ask(1,1,n,w[x]+1,w[y]));
}

void update(int x,int y)
{
	_update(1,1,n,w[pos[x]],y);
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int a,b,c;
	char s[100];
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		_connect(a,b,c);
		_connect(b,a,c);
	}
	dfs1(1,0,0);
	dfs2(1,1);
	for (int i=1;i<=n;i++)
		rw[w[i]]=i;
	_build(1,1,n);
	while(1)
	{
		scanf("%s",s);
		if (s[0]=='D')
			break;
		scanf("%d%d",&a,&b);
		if (s[0]=='Q')
			printf("%d\n",ask(a,b));
		else
			update(a,b);
	}
	return 0;
}