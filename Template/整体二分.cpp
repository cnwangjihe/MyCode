#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

const bool R = 0,
		   L = 1;
const int MAXN = 50006,
		  MAXM = 50006;

struct Twork
{
	int t,x,y,z,id;
};

struct Tnode
{
	long long v;
	int add,size;
	Tnode()
	{
		v=0ll;
		add=size=0;
	}
};

Twork a[MAXM],b[MAXM];
Tnode tree[MAXN*8];
int ans[MAXM];
bool lr[MAXM];
int n,m,anscnt,Maxnum;

void down(int root)
{
	tree[root*2].add+=tree[root].add;
	tree[root*2+1].add+=tree[root].add;
	tree[root*2].v+=tree[root].add*tree[root*2].size;
	tree[root*2+1].v+=tree[root].add*tree[root*2+1].size;
	tree[root].add=0;
}
int _build(int root,int l,int r)
{
	if (l==r) 
	{
		tree[root].size=1;
		return tree[root].size;
	}
	int mid=(l+r)/2;
	tree[root].size=_build(root*2,l,mid)+_build(root*2+1,mid+1,r);
	return tree[root].size;
}
long long _ask(int root,int l,int r,int al,int ar)
{
	if (l>=al && r<=ar) return tree[root].v;
	down(root);
	int mid=(l+r)/2;
	long long ans=0;
	if (al<=mid) ans+=_ask(root*2,l,mid,al,ar);
	if (ar>mid) ans+=_ask(root*2+1,mid+1,r,al,ar);
	return ans;
}

void _update(int root,int l,int r,int al,int ar,int v)
{
	if (l>=al && r<=ar) 
	{
		tree[root].add+=v;
		tree[root].v+=tree[root].size*v;
		return ;
	}
	down(root);
	int mid=(l+r)/2;
	if (al<=mid) _update(root*2,l,mid,al,ar,v);
	if (ar>mid) _update(root*2+1,mid+1,r,al,ar,v);
	tree[root].v=tree[root*2].v+tree[root*2+1].v;
	return ;
}

void solve(int x,int y,int l,int r)
{
	long long cnt;
	int p1=x,p2=x;
	int mid=(l+r)/2;
	if (l==r)
	{
		for (int i=x;i<=y;i++) 
			if (a[i].t) ans[a[i].id]=l;
		return ;
	}
	for (int i=x;i<=y;i++)
	{
		if (a[i].t)
		{
			cnt=_ask(1,1,Maxnum,a[i].x,a[i].y);
			if (cnt<a[i].z) 
			{
				lr[i]=R;
				a[i].z-=int(cnt);
			}
			else
			{
				lr[i]=L;
				p2++;
			}
		}
		else
		{
			if (a[i].z<=mid) 
			{
				lr[i]=L;p2++;
				_update(1,1,Maxnum,a[i].x,a[i].y,1);
			}
			else lr[i]=R;
		}
	}
	for (int i=x;i<=y;i++)
		if (!a[i].t && a[i].z<=mid) _update(1,1,Maxnum,a[i].x,a[i].y,-1);
	for (int i=x;i<=y;i++)
		if (lr[i]==L)
			b[p1++]=a[i];
		else 
			b[p2++]=a[i];
	for (int i=x;i<=y;i++) a[i]=b[i];
	solve(x,p1-1,l,mid);
	solve(p1,y,mid+1,r);
	return ;
}

int main()
{
	int t;
	anscnt=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&t,&a[i].x,&a[i].y,&a[i].z);
		a[i].t=bool(t-1);
		if (!a[i].t) 
		{
			a[i].z=n-a[i].z+1;
			Maxnum=max(Maxnum,a[i].z);
		}
		else a[i].id=anscnt++;
	}
	_build(1,1,Maxnum);
	solve(1,m,1,Maxnum);
	for (int i=0;i<anscnt;i++)
		printf("%d\n",n-ans[i]+1);
	return 0;
}