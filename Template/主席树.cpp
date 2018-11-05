#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct Tnode{int v,lc,rc;};

const int MAXN = 200009;

Tnode t[MAXN<<5];
int x[MAXN],v[MAXN],p[MAXN],h[MAXN];
int n,m,fp=1;

bool _cmp(int a,int b) {return v[a]<v[b];}

int _copy(int u)
{
	t[fp]=t[u];
	return fp++;
}

int _build(int l,int r)
{
	int u=fp++;
	if (l==r)
		return u;
	int mid=(l+r)/2;
	t[u].lc=_build(l,mid);
	t[u].rc=_build(mid+1,r);
	return u;
}

int _inc(int u,int l,int r,int p,int v)
{
	u=_copy(u);
	if (l==r)
	{
		t[u].v+=v;
		return u;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		t[u].lc=_inc(t[u].lc,l,mid,p,v);
	else
		t[u].rc=_inc(t[u].rc,mid+1,r,p,v);
	t[u].v=t[t[u].lc].v+t[t[u].rc].v;
	return u;
}

int _query(int u,int v,int l,int r,int k)
{
	if (l==r)
		return l;
	int mid=(l+r)/2,x=t[t[v].lc].v-t[t[u].lc].v;
	if (k<=x)
		return _query(t[u].lc,t[v].lc,l,mid,k);
	else
		return _query(t[u].rc,t[v].rc,mid+1,r,k-x);
}

int main()
{
	int l,r,k;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]),p[i]=i;
	sort(p+1,p+1+n,_cmp);
	int cnt=1;
	for (int i=1;i<=n;i++)
	{
		while (i<n && v[p[i]]==v[p[i+1]])
			v[p[i]]=cnt,i++;
		x[cnt]=v[p[i]];
		v[p[i]]=cnt++;
	}
	cnt--;
	_build(1,cnt);
	for (int i=1;i<=n;i++)
		h[i]=_inc(h[i-1],1,cnt,v[i],1);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",x[_query(h[l-1],h[r],1,cnt,k)]);
	}
	return 0;
}