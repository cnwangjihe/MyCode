#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int resa = (1<<22)-1,
		  reso = 0,
		  MAXN = 200009;

struct Tnode {int A,O;Tnode(){A=resa;O=reso;}};

Tnode t[MAXN*4];
int val[MAXN];
int n,m;

void _down(int u)
{
	t[u*2].A|=t[u].O;
	t[u*2].O|=t[u].O;
	t[u*2].A&=t[u].A;
	t[u*2+1].A|=t[u].O;
	t[u*2+1].O|=t[u].O;
	t[u*2+1].A&=t[u].A;
	t[u].O=reso,t[u].A=resa;
	return ;
}

void _and(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		t[u].A&=v;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (al<=mid)
		_and(u*2,l,mid,al,ar,v);
	if (ar>mid)
		_and(u*2+1,mid+1,r,al,ar,v);
}

void _or(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		if (l==r)
		{
			val[l]|=t[u].O;
			val[l]&=t[u].A;
			t[u].O=reso;t[u].A=resa;
		}
		else
			_down(u);
		t[u].O|=v;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (al<=mid)
		_or(u*2,l,mid,al,ar,v);
	if (ar>mid)
		_or(u*2+1,mid+1,r,al,ar,v);
}

int _ask(int u,int l,int r,int p)
{
	if (l==r)
	{
		val[l]|=t[u].O;
		val[l]&=t[u].A;
		t[u].O=reso;t[u].A=resa;
		return val[l];
	}
	int mid=(l+r)/2;
	_down(u);
	if (p<=mid)
		return _ask(u*2,l,mid,p);
	else
		return _ask(u*2+1,mid+1,r,p);
}

void work0()
{
	int ans,t,a,b,v;
	for (int i=0;i<m;i++)
	{
		scanf("%d",&t);
		if (t==1)
		{
			scanf("%d%d%d",&a,&b,&v);
			for (int j=a;j<=b;j++)
				val[j]&=v;
		}
		if (t==2)
		{
			scanf("%d%d%d",&a,&b,&v);
			for (int j=a;j<=b;j++)
				val[j]|=v;
		}
		if (t==3)
		{
			ans=0;
			scanf("%d%d",&a,&b);
			for (int j=a;j<=b;j++)
				ans=max(ans,val[j]);
			printf("%d\n",ans);
		}
	}
}

int main()
{
	freopen("girl.in","r",stdin);
	freopen("girl.out","w",stdout);
	int a,b,v,t;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	if (n*m<=800000000)
	{
		work0();
		return 0;
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d",&t);
		if (t==1)
		{
			scanf("%d%d%d",&a,&b,&v);
			_and(1,1,n,a,b,v);
		}
		if (t==2)
		{
			scanf("%d%d%d",&a,&b,&v);
			_or(1,1,n,a,b,v);
		}
		if (t==3)
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",_ask(1,1,n,a));
		}
	}
	return 0;
}