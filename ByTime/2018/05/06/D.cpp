#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009;
const long long INF = 1e18;

int n,m;
int a[MAXN];
long long Max[MAXN*4],add[MAXN*4],cover[MAXN*4];
long long _Max[MAXN*4],_add[MAXN*4],_cover[MAXN*4];
long long ans;

void update(int u)
{
	Max[u]=max(Max[u*2],Max[u*2+1]);
	_Max[u]=max(_Max[u*2],_Max[u*2+1]);
}

void pushdown(int u)
{
	int son;
	for (int i=0;i<=1;i++)
	{
		son=u*2+i;
		_Max[son]=max(_Max[son],max(_cover[u],Max[son]+_add[u]));
		if (cover[son]==-INF) _add[son]=max(_add[son],add[son]+_add[u]);
		else _cover[son]=max(_cover[son],cover[son]+_add[u]);
		if (add[u])
		{
			if (cover[son]!=-INF) cover[son]+=add[u];
			else add[son]+=add[u];
			Max[son]+=add[u];
		}
		if (cover[u]!=-INF)
		{
			Max[son]=cover[son]=cover[u];
			add[son]=0;
		}
		_cover[son]=max(_cover[son],max(cover[son],_cover[u]));
		_add[son]=max(_add[son],add[son]);
	}
	add[u]=_add[u]=0;
	cover[u]=_cover[u]=-INF;
	return ;
}

void build(int u,int l,int r)
{
	add[u]=_add[u]=0;
	cover[u]=_cover[u]=-INF;
	if (l==r)
	{
		Max[u]=(long long)a[l];
		_Max[u]=(long long)a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	update(u);
	return ;
}

void change(int u,int l,int r,int al,int ar,long long x,int opt)
{
	if (al<=l && r<=ar)
	{
		if (l!=r)
			pushdown(u);
		if (!opt)
			Max[u]+=x,add[u]+=x,_add[u]+=x;
		else
			cover[u]=_cover[u]=Max[u]=x;
		_Max[u]=max(_Max[u],Max[u]);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(u);
	if (al<=mid)
		change(u*2,l,mid,al,ar,x,opt);
	if (mid<ar)
		change(u*2+1,mid+1,r,al,ar,x,opt);
	update(u);
	return ;
}

long long query(int u,int l,int r,int al,int ar,int opt)
{
	if (al<=l && r<=ar)
		return (opt?_Max[u]:Max[u]);
	int mid=(l+r)>>1;
	long long ans=-INF;
	pushdown(u);
	if (al<=mid)
		ans=max(ans,query(u*2,l,mid,al,ar,opt));
	if (mid+1<=ar)
		ans=max(ans,query(u*2+1,mid+1,r,al,ar,opt));
	return ans;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	int l,r,x;
	char opt;
	for (int i=1;i<=m;i++)
	{
		do {opt=getchar();}
			while (opt!='Q' && opt!='A' && opt!='P' && opt!='C');

		if (opt=='Q')
		{
			scanf("%d%d",&l,&r);
			ans=query(1,1,n,l,r,0);
			printf("%lld\n",ans);
		}
		if (opt=='A')
		{
			scanf("%d%d",&l,&r);
			ans=query(1,1,n,l,r,1);
			printf("%lld\n",ans);
		}
		if (opt=='P')
		{
			scanf("%d%d%d",&l,&r,&x);
			change(1,1,n,l,r,(long long)x,0);
		}
		if (opt=='C')
		{
			scanf("%d%d%d",&l,&r,&x);
			change(1,1,n,l,r,(long long)x,1);
		}
	}
	return 0;
}