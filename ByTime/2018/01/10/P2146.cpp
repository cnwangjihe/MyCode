#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode
{
	int sum,num,cnt;
	void reset() {sum=cnt=0;num=-1;}
};

const int MAXN = 100009;

bool type;
int n,m,x,tmp,tim=0,fp=0;
int dep[MAXN],siz[MAXN],fa[MAXN],son[MAXN],w[MAXN],top[MAXN];
int _head[MAXN],_next[MAXN],_node[MAXN];
Tnode tree[MAXN*4];

void _down(int u)
{
	if (!(~tree[u].num)) return ;
	tree[u*2].sum=tree[u].num*tree[u*2].cnt;
	tree[u*2+1].sum=tree[u].num*tree[u*2+1].cnt;
	tree[u*2].num=tree[u].num;
	tree[u*2+1].num=tree[u].num;
	tree[u].num=-1;
	return ;
}

void _up(int u)
{
	tree[u].sum=tree[u*2].sum+tree[u*2+1].sum;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		tree[u].cnt=1;
		tree[u].num=-1;
		tree[u].sum=0;
		return ;
	}
	int mid=(l+r)>>1;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	tree[u].cnt=tree[u*2].cnt+tree[u*2+1].cnt;
	return ;
}

int _ask(int u) {return tree[u].sum;}

void _update(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		tree[u].sum=tree[u].cnt*v;
		tree[u].num=v;
		return ;
	}
	_down(u);
	int mid=(l+r)>>1;
	if (al<=mid) _update(u*2,l,mid,al,ar,v);
	if (ar>mid) _update(u*2+1,mid+1,r,al,ar,v);
	_up(u);
	return ;
}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs1(int u,int fat)
{
	fa[u]=fat;
	dep[u]=dep[fat]+1;
	siz[u]=1;
	son[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		dfs1(_node[i],u);
		if (siz[son[u]]<siz[_node[i]])
			son[u]=_node[i];
		siz[u]+=siz[_node[i]];
	}
	return ;
}

void dfs2(int u,int t)
{
	w[u]=++tim;
	top[u]=t;
	if (!son[u]) return ;
	dfs2(son[u],top[u]);
	for (int i=_head[u];~i;i=_next[i])
		if (son[u]!=_node[i])
			dfs2(_node[i],_node[i]);
	return ;
}

int Update(int a,int b,int v)
{
	while (top[a]!=top[b])
	{
		if (dep[top[a]]<dep[top[b]])
			swap(a,b);
		_update(1,1,n,w[top[a]],w[a],v);
		a=fa[top[a]];
	}
	if (dep[a]<dep[b])
		swap(a,b);
	_update(1,1,n,w[b],w[a],v);
	return _ask(1);
}

int Update(int a,int v)
{
	_update(1,1,n,w[a],w[a]+siz[a]-1,v);
	return _ask(1);
}

bool _Gets()
{
	char c;
	bool ans;
	do {c=getchar();}
		while (c<'a' || c>'z');
	ans=(c=='i')?1:0;
	do {c=getchar();}
		while (c>='a' && c<='z');
	return ans;
}

int main()
{
//	freopen("P2146.in","r",stdin);
	memset(_head,-1,sizeof _head);
	scanf("%d",&n);
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		_connect(x+1,i);
	}
	tim=0;
	dfs1(1,1);
	dfs2(1,1);
	_build(1,1,n);
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		type=_Gets();
		scanf("%d",&x);
		tmp=_ask(1);
		if (type)
			printf("%d\n",Update(1,x+1,1)-tmp);
		else
			printf("%d\n",tmp-Update(x+1,0));
	}
	return 0;
}