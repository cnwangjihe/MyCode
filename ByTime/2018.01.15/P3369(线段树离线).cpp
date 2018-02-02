#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode {int cnt,lt,rt;};
struct Tquery {int type,v,i;};

const int MAXN = 100009;

Tnode t[MAXN*4];
Tquery q[MAXN],p[MAXN];
int n=0,m,k=0;
int real[MAXN];

bool _cmp1(Tquery a,Tquery b) {return a.v<b.v;}
bool _cmp2(Tquery a,Tquery b) {return a.i<b.i;}

void _up(int u)
{
	t[u].cnt=t[u*2].cnt+t[u*2+1].cnt;
	t[u].lt=(~t[u*2].lt)?t[u*2].lt:t[u*2+1].lt;
	t[u].rt=(~t[u*2+1].rt)?t[u*2+1].rt:t[u*2].rt;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].cnt=0;
		t[u].lt=t[u].rt=-1;
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	_up(u);
	return ;
}

void _add(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u].cnt+=v;
		if (t[u].cnt)
			t[u].lt=t[u].rt=l;
		else
			t[u].lt=t[u].rt=-1;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_add(u*2,l,mid,p,v);
	else
		_add(u*2+1,mid+1,r,p,v);
	_up(u);
	return ;
}

int _askrank(int u,int l,int r,int v)
{
	if (l==r)
		return v>l;
	int mid=(l+r)/2;
	if (v<=mid)
		return _askrank(u*2,l,mid,v);
	else
		return t[u*2].cnt+_askrank(u*2+1,mid+1,r,v);
}

int _askvalue(int u,int l,int r,int v)
{
	if (l==r)
		return l;
	int mid=(l+r)/2;
	if (t[u*2].cnt>=v)
		return _askvalue(u*2,l,mid,v);
	else
		return _askvalue(u*2+1,mid+1,r,v-t[u*2].cnt);
}

int _askpre(int u,int l,int r,int x)
{
	if (l==r)
		return -1;
	int mid=(l+r)/2,ans;
	if (x<=mid)
		return _askpre(u*2,l,mid,x);
	else
		ans=_askpre(u*2+1,mid+1,r,x);
	return (~ans)?ans:t[u*2].rt;
}

int _asknxt(int u,int l,int r,int x)
{
	if (l==r)
		return -1;
	int mid=(l+r)/2,ans;
	if (x<=mid)
		ans=_asknxt(u*2,l,mid,x);
	else
		return _asknxt(u*2+1,mid+1,r,x);
	return (~ans)?ans:t[u*2+1].lt;
}

int main()
{
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].type,&q[i].v);
		q[i].i=i;
		if (q[i].type!=4) p[++k]=q[i];
	}
	sort(p+1,p+k+1,_cmp1);
	for (int i=1;i<=k;i++)
	{
		real[++n]=p[i].v;
		q[p[i].i].v=n;
		while (i+1<=k && p[i].v==p[i+1].v)
			q[p[++i].i].v=n;
	}
//	for (int i=1;i<=m;i++)
//	{
//		printf("%d ",q[i].v);
//	}
//	printf("\n");
	_build(1,1,n);
	for (int i=1;i<=m;i++)
	{
		if (q[i].type==1) _add(1,1,n,q[i].v,1);
		if (q[i].type==2) _add(1,1,n,q[i].v,-1);
		if (q[i].type==3) printf("%d\n",_askrank(1,1,n,q[i].v)+1);
		if (q[i].type==4) printf("%d\n",real[_askvalue(1,1,n,q[i].v)]);
		if (q[i].type==5) printf("%d\n",real[_askpre(1,1,n,q[i].v)]);
		if (q[i].type==6) printf("%d\n",real[_asknxt(1,1,n,q[i].v)]);
	}
	return 0;
}
