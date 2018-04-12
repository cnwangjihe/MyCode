#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode{int v;bool zero;};
struct Tpoint{int x,y,t,i;};

const int MAXN = 200009;

Tnode t[MAXN*4];
Tpoint node[MAXN],b[MAXN];
int ans[MAXN],col[MAXN];
int n,m=0,q;

bool _cmpx(Tpoint a,Tpoint b){return a.x==b.x?a.t<b.t:a.x<b.x;}
bool _cmpy(Tpoint a,Tpoint b){return a.y<b.y;}

inline void _up(int u)
{
	t[u].v=t[u*2].v+t[u*2+1].v;
	return ;
}

inline void _down(int u)
{
	if (!t[u].zero)
		return ;
	t[u*2].zero=t[u*2+1].zero=1;
	t[u*2].v=t[u*2+1].v=0;
	t[u].zero=0;
	return ;
}

void _change(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
	{
		t[u].zero=1;
		t[u].v=0;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (al<=mid)
		_change(u*2,l,mid,al,ar);
	if (ar>mid)
		_change(u*2+1,mid+1,r,al,ar);
	_up(u);
	return ;
}

void _inc(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u].v+=v;
		return ;
	}
	int mid=(l+r)/2;
	_down(u);
	if (p<=mid)
		_inc(u*2,l,mid,p,v);
	else
		_inc(u*2+1,mid+1,r,p,v);
	_up(u);
}

int _ask(int u,int l,int r,int p)
{
	if (l==r)
		return t[u].v;
	int mid=(l+r)/2;
	_down(u);
	if (p<=mid)
		return _ask(u*2,l,mid,p);
	else
		return _ask(u*2+1,mid+1,r,p);
}

void solve(int l,int r,int al,int ar)
{
	if (al==ar)
	{
		int tmp,c=0;
	//	cerr << al << ":\n";
		for (int i=l;i<=r;i++)
			if (node[i].t)
				tmp=i;
		for (int i=l;i<=r;i++)
			if (!node[i].t && node[i].x<=node[tmp].x && node[i].y<=node[tmp].y)
				c++;;//,cerr << node[i].x << ' ' << node[i].y << '\n';
		ans[node[tmp].i]=c;
	//	cerr << '\n';
		return ;
	}
	int mid=(al+ar)/2,k1=l,k2=l;
	for (int i=l;i<=r;i++)
	{
		if (!node[i].t)
			_inc(1,1,m,node[i].y,1);
		else
		{
			if (node[i].i>mid)
				col[i]=1;
			else
				col[i]=0,k2++,_change(1,1,m,1,node[i].y);
		}
	}
	for (int i=r;i>=l;i--)
	{
		if (node[i].t)
			continue;
		if (_ask(1,1,m,node[i].y)>0)
			col[i]=1;
		else
			col[i]=0,k2++;
		_inc(1,1,m,node[i].y,-1);
	}
	for (int i=l;i<=r;i++)
		if (col[i])
			b[k2++]=node[i];
		else
			b[k1++]=node[i];
	for (int i=l;i<=r;i++)
		node[i]=b[i];
	solve(l,k1-1,al,mid);
	solve(k1,r,mid+1,ar);
}

void work0()
{
	const int INF = 1000000009;
	int x[1006],y[1006],ans,tx[1006],ty[1006],a,b;
	fill(tx,tx+n,INF);
	fill(ty,ty+n,INF);
	for (int i=0;i<n;i++)
		scanf("%d%d",&x[i],&y[i]);
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		ans=0;
		scanf("%d%d",&a,&b);
		for (int i=0;i<n;i++)
			if (tx[i]>=a && ty[i]>=b && x[i]<=a && y[i]<=b)
				ans++,tx[i]=a,ty[i]=b;
		printf("%d\n",ans);
	}
}

int main()
{
	freopen("2439.in","r",stdin);
	freopen("2439.out","w",stdout);
	scanf("%d",&n);
	if (n<=1000 && q<=1000)
	{
		work0();
		return 0;
	}
	for (int i=0;i<n;i++)
		scanf("%d%d",&node[i].x,&node[i].y),node[i].t=0;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
		scanf("%d%d",&node[i+n].x,&node[i+n].y),node[i+n].t=1,node[i+n].i=i;
	sort(node,node+n+q,_cmpy);
	for (int i=0;i<n+q;i++)
	{
		node[i].y=++m;
		while (i<n+q && node[i].y==node[i+1].y)
			node[++i].y=m;
	}
	sort(node,node+n+q,_cmpx);
	solve(0,n+q-1,0,q-1);
	for (int i=0;i<q;i++)
		printf("%d\n",ans[i]);
	return 0;
}