#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 40009;

struct Tnode{int Sum,Max;};

Tnode t[MAXN*4];
int _node[MAXN*2],_next[MAXN*2],_head[MAXN];
int fa[MAXN],w[MAXN],son[MAXN],deep[MAXN];
int rw[MAXN],size[MAXN],top[MAXN],d[MAXN];
int n,m,q,ti=0,fp=0;
bool f[MAXN];
char c[12];

inline void Pushup(int u)
{
	t[u].Max=max(t[u*2].Max,t[u*2+1].Max);
	t[u].Sum=t[u*2].Sum+t[u*2+1].Sum;
	return ;
} 

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].Sum=t[u].Max=d[rw[l]];
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	Pushup(u);
	return ;
}

void _update(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u].Sum=t[u].Max=v;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_update(u*2,l,mid,p,v);
	else
		_update(u*2+1,mid+1,r,p,v);
	Pushup(u);
}

int _asksum(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u].Sum;
	int mid=(l+r)/2,ans=0;
	if (al<=mid)
		ans+=_asksum(u*2,l,mid,al,ar);
	if (ar>mid)
		ans+=_asksum(u*2+1,mid+1,r,al,ar);
	return ans;
}

int _askmax(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u].Max;
	int mid=(l+r)/2,ans=-300009;
	if (al<=mid)
		ans=max(ans,_askmax(u*2,l,mid,al,ar));
	if (ar>mid)
		ans=max(ans,_askmax(u*2+1,mid+1,r,al,ar));
	return ans;
}

inline void _add(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b)
{
	_add(a,b);
	_add(b,a);
	return ;
}

int dfs1(int p,int fath)
{
	int tmp;
	fa[p]=fath;
	deep[p]=deep[fath]+1;
	for (int i=_head[p];~i;i=_next[i])
	{
		if (f[_node[i]])
			continue;
		f[_node[i]]=1;
		tmp=dfs1(_node[i],p);
		if (tmp>size[son[p]]) son[p]=_node[i];
		size[p]+=tmp;
	}
	size[p]++;
	return size[p];
}

void dfs2(int p,int t)
{
	if (p==0) return ;
	ti++;
	w[p]=ti;
	top[p]=t;
	f[son[p]]=1;
	dfs2(son[p],top[p]);
	for (int i=_head[p];~i;i=_next[i])
	{
		if (f[_node[i]])
			continue;
		f[_node[i]]=1;
		dfs2(_node[i],_node[i]);
	}
	return ;
}

void Change(int p,int v) {_update(1,1,n,w[p],v);}

int Asksum(int a,int b)
{
	int ans=0;
	while (top[a]!=top[b])
	{
		if (deep[top[a]]<deep[top[b]])
			swap(a,b);
		ans+=_asksum(1,1,n,w[top[a]],w[a]);
		a=fa[top[a]];
	}
	if (deep[a]<deep[b]) swap(a,b);
	ans+=_asksum(1,1,n,w[b],w[a]);
	return ans;
}

int Askmax(int a,int b)
{
	int ans=-3000009;
	while (top[a]!=top[b])
	{
		if (deep[top[a]]<deep[top[b]])
			swap(a,b);
		ans=max(ans,_askmax(1,1,n,w[top[a]],w[a]));
	//	cerr << ans << endl;
		a=fa[top[a]];
	}
	if (deep[a]<deep[b])
		swap(a,b);
	ans=max(ans,_askmax(1,1,n,w[b],w[a]));
	return ans;
}

int main()
{
	int a,b;
	scanf("%d",&n);
	memset(_head,-1,sizeof _head);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
	}
	for (int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	scanf("%d",&q);
	memset(f,0,sizeof f);
	f[1]=1;
	dfs1(1,0);
	memset(f,0,sizeof f);
	f[1]=1;
	dfs2(1,1);
	for (int i=1;i<=n;i++)
		rw[w[i]]=i;
	_build(1,1,n);
	for (int i=0;i<q;i++)
	{
		do {c[0]=getchar();}
			while (c[0]!='C' && c[0]!='Q');
		c[1]=getchar();
		if (c[0]=='C')
		{
			scanf("%s%d%d",c,&a,&b);
	//		printf("1 %d %d\n",a,b);
			Change(a,b);
		}
		else
		{
			if (c[1]=='S')
			{
				scanf("%s%d%d",c,&a,&b);
	//			printf("2 %d %d\n",a,b);
				printf("%d\n",Asksum(a,b));
			}
			else
			{
				scanf("%s%d%d",c,&a,&b);
	//			printf("3 %d %d\n",a,b);
				printf("%d\n",Askmax(a,b));
			}
		}
	}
	return 0;
}