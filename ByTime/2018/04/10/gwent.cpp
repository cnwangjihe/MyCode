#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct Tnode{int a,b;};

const int MAXN = 200009;

Tnode t[MAXN*4];
int a[MAXN],b[MAXN];
int n,m;

void _up(int u,int p)
{
	if (t[u*2].a==-1)
		t[u].a=-1;
	else
		if (t[u*2].a<=a[p])
			t[u].a=t[u*2+1].a;
		else
			if (t[u*2].a<=b[p])
				t[u].a=t[u*2+1].b;
			else
				t[u].a=-1;
	if (t[u*2].b==-1)
		t[u].b=-1;
	else
		if (t[u*2].b<=a[p])
			t[u].b=t[u*2+1].a;
		else
			if (t[u*2].b<=b[p])
				t[u].b=t[u*2+1].b;
			else
				t[u].b=-1;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].a=a[l];
		t[u].b=b[l];
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	_up(u,mid+1);
	return ;
}

void _update(int u,int l,int r,int p,int a,int b)
{
	if (l==r)
	{
		t[u].a=a;
		t[u].b=b;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_update(u*2,l,mid,p,a,b);
	else
		_update(u*2+1,mid+1,r,p,a,b);
	_up(u,mid+1);
	return ;
}

bool _ask(){return (~t[1].a)||(~t[1].b);}

int main()
{
	freopen("gwent.in","r",stdin);
	freopen("gwent.out","w",stdout);
	int p1,p2;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		if (a[i]>b[i])
			swap(a[i],b[i]);
	}
	_build(1,1,n);
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&p1,&p2);
		swap(a[p1],a[p2]);
		swap(b[p1],b[p2]);
		_update(1,1,n,p1,a[p1],b[p1]);
		_update(1,1,n,p2,a[p2],b[p2]);
		printf("%s\n",_ask()?"YES":"NO");
	}
	return 0;
}