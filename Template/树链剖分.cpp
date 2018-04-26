#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 50002,
		  MAXM = 50001;

int node[MAXM*2],_next[MAXM*2],head[MAXN],tp;
int fa[MAXN],w[MAXN],son[MAXN],deep[MAXN],rw[MAXN],size[MAXN],top[MAXN];
bool f[MAXN];
long long tree[MAXN*4],ad[MAXN*4];
int cnt[MAXN*4];
int d[MAXN];
int ti,n,m,q,a,b,value;
char c;

void connect(int a,int b)
{
	_next[tp]=head[a];
	head[a]=tp;
	node[tp]=b;
	tp++;
	return ;
}

long long _build(int root,int l,int r)
{
	if (l==r) 
	{
		tree[root]=d[rw[l]];
		cnt[root]=1;
		return tree[root];
	}
	int mid=(l+r)/2;
	tree[root]=_build(root*2,l,mid)+_build(root*2+1,mid+1,r);
	cnt[root]=cnt[root*2]+cnt[root*2+1];
	return tree[root];
}

void _down(int root)
{
	ad[root*2]+=ad[root];
	ad[root*2+1]+=ad[root];
	tree[root*2]+=cnt[root*2]*ad[root];
	tree[root*2+1]+=cnt[root*2+1]*ad[root];
	ad[root]=0;
	return ;
}

long long _ask(int root,int l,int r,int p)
{
	if (l==r) return tree[root];
	_down(root);
	int mid=(l+r)/2;
	if (p<=mid) return _ask(root*2,l,mid,p);
	else return _ask(root*2+1,mid+1,r,p);
}

void _add(int root,int l,int r,int al,int ar,int value)
{
	if (l>=al && r<=ar)
	{
		ad[root]+=value;
		tree[root]+=value*cnt[root];
		return ;
	}
	_down(root);
	int mid=(l+r)/2;
	if (al<=mid) _add(root*2,l,mid,al,ar,value);
	if (ar>mid) _add(root*2+1,mid+1,r,al,ar,value);
	tree[root]=tree[root*2]+tree[root*2+1];
	return ;
}

int dfs1(int p,int fath)
{
	int tmp;
	fa[p]=fath;
	deep[p]=deep[fath]+1;
	for (int i=head[p];i!=-1;i=_next[i])
	{
		if (f[node[i]]) continue;
		f[node[i]]=1;
		tmp=dfs1(node[i],p);
		if (tmp>size[son[p]]) son[p]=node[i];
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
	for (int i=head[p];i!=-1;i=_next[i])
	{
		if (f[node[i]]) continue;
		f[node[i]]=1;
		dfs2(node[i],node[i]);
	}
	return ;
}
long long ask(int a)
{
	return _ask(1,1,n,w[a]);
}

void add(int a,int b,int value)
{
	while (top[a]!=top[b])
	{
		if (deep[top[a]]<deep[top[b]]) swap(a,b);
		_add(1,1,n,w[top[a]],w[a],value);
		a=fa[top[a]];
	}
	if (deep[a]<deep[b]) swap(a,b);
//	cerr << a << b << endl;
	_add(1,1,n,w[b],w[a],value);
	return ;
}

int main()
{
//	freopen("HDU3966.in","r",stdin);
//	freopen("HDU3966.out","w",stdout);
	while (scanf("%d%d%d",&n,&m,&q) != EOF)
	{
		tp=ti=0;
		memset(head,-1,sizeof head);
		memset(size,0,sizeof size);
		memset(son,0,sizeof son);
		memset(size,0,sizeof size);
		memset(top,0,sizeof top);
		memset(ad,0,sizeof ad);
		memset(cnt,0,sizeof cnt);
		deep[0]=0;
		for (int i=1;i<=n;i++) scanf("%d",&d[i]);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			connect(a,b);
			connect(b,a);
		}
		memset(f,0,sizeof f);
		f[1]=1;
		dfs1(1,0);
		memset(f,0,sizeof f);
		f[1]=1;
		dfs2(1,1);
		for (int i=1;i<=n;i++) rw[w[i]]=i;
		_build(1,1,n);
//		cerr << endl;
//		for (int i=1;i<=10;i++) cerr << tree[i] << " ";
//		cerr << endl;
//		for (int i=1;i<=n;i++) cerr << i << ": "<< deep[i] << " " << size[i] << " " << son[i] << " " << w[i] << endl;
		for (int i=0;i<q;i++)
		{
			do
			{
				scanf("%c",&c);
			}while (c!='I' && c!='D' && c!='Q');
			if (c=='I')
			{
				scanf("%d%d%d",&a,&b,&value);
				add(a,b,value);
			}
			else
			if (c=='D')
			{
				scanf("%d%d%d",&a,&b,&value);
				add(a,b,-value);
//				cerr << endl;
//				for (int i=1;i<=10;i++) cerr << tree[i] << " ";
//				cerr << endl;
			}
			else
		{
				scanf("%d",&a);
	//			cerr << endl;
//				for (int i=1;i<=10;i++) cerr << tree[i] << " ";
//				cerr << endl;
				printf("%lld\n",ask(a));
			}
		}
	}
	return 0;
}