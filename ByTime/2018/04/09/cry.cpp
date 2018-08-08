#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode{int v,add;};

const int MAXN = 200009,
		  INF  = 1000000009;

Tnode t[MAXN*4];
int sum[MAXN*2];
int a[MAXN],b[MAXN],c[MAXN],v[MAXN];
int n,m,h;

bool _cmp(int a,int b) {return a>b;}

void Inc(int k,int v)
{
//	cerr << "Inc";
	for (;k<=m+1;k+=(k & (-k)))
		sum[k]+=v;
	return ;
}

int Ask(int k)
{
//	cerr << "Ask";
	int ans=0;
	for (;k;k-=(k & (-k)))
		ans+=sum[k];
	return ans;
}

inline void _up(int u)
{
	t[u].v=min(t[u*2].v,t[u*2+1].v);
	return ;
}

inline void _down(int u)
{
	if (!t[u].add)
		return ;
	t[u*2].v+=t[u].add,t[u*2+1].v+=t[u].add;
	t[u*2].add+=t[u].add,t[u*2+1].add+=t[u].add;
	t[u].add=0;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].v=v[l];
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	_up(u);
	return ;
}

void _add(int u,int l,int r,int al,int ar,int v)
{
//	cerr << 'a' <<'\n';
	if (al<=l && ar>=r)
	{
		t[u].v+=v;
		t[u].add+=v;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (al<=mid)
		_add(u*2,l,mid,al,ar,v);
	if (ar>mid)
		_add(u*2+1,mid+1,r,al,ar,v);
	_up(u);
	return ;
}

int _ask(int u,int l,int r,int al,int ar)
{
//	cerr << 'k' << endl;
	if (al<=l && ar>=r)
		return t[u].v;
	int mid=(l+r)/2,ans=INF;
	_down(u);
	if (al<=mid)
		ans=min(ans,_ask(u*2,l,mid,al,ar));
	if (ar>mid)
		ans=min(ans,_ask(u*2+1,mid+1,r,al,ar));
	return ans;
}

void _change(int u,int l,int r,int p,int v)
{
//	cerr << 'c' << endl;
	if (l==r)
	{
		t[u].v=v;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (p<=mid)
		_change(u*2,l,mid,p,v);
	else
		_change(u*2+1,mid+1,r,p,v);
	_up(u);
	return ;
}

int _find(int k)
{
	int l=0,r=m+1,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (b[mid]>=k)
			l=mid;
		else
			r=mid;
	}
	return l+1;
}

int main()
{
	freopen("cry.in","r",stdin);
	freopen("cry.out","w",stdout);
	int ans=0;
	fill(v,v+MAXN,INF);
	scanf("%d%d%d",&n,&m,&h);
	for (int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	sort(b+1,b+1+m,_cmp);    
	for (int i=1;i<=n;i++)
	{
	   scanf("%d",&a[i]);
	   c[i]=_find(h-a[i]);
	}
	v[n+1]=0;
	for (int i=1;i<=m;i++)
		Inc(c[i],1);
	for (int i=1;i<=m;i++)
		v[c[i]]=c[i]-Ask(c[i]);
	int tmp;
	_build(1,1,m+1);
	for (int i=m+1;i<=n;i++)
	{
//		cerr << i << endl;
		ans+=t[1].v>=1?1:0;
		if (c[i-m]!=c[i])
		{
//			cerr << "fsdf";
			Inc(c[i-m],-1),Inc(c[i],1);
			tmp=Ask(c[i]);
			if (Ask(c[i-m])==Ask(c[i-m]-1))
				_change(1,1,m+1,c[i-m],INF);
			if (tmp==Ask(c[i]-1)+1)
				_change(1,1,m+1,c[i],c[i]-tmp);
			if (c[i]>c[i-m])
				_add(1,1,m+1,c[i-m],c[i]-1,1);
			else 
				if (c[i]<c[i-m])
					_add(1,1,m+1,c[i],c[i-m]-1,-1);
		}
	}
	printf("%d\n",ans+=t[1].v>=1?1:0);
	return 0;
}