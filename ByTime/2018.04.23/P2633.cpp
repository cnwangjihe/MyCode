#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode{int lc,rc,v;};

const int MAXN = 100009;

int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int v[MAXN],jump[MAXN][18],h[MAXN],dep[MAXN],p[MAXN],x[MAXN];
Tnode t[MAXN<<5];
int tp=0,fp=1,cnt=1;
int n,m;

void _connect(int a,int b)
{
	_next[tp]=_head[a];
	_node[tp]=b;
	_head[a]=tp++;
	return ;
}

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

int _query(int a,int b,int c,int d,int l,int r,int k)
{
	if (l==r)
		return l;
	int mid=(l+r)/2,x=t[t[a].lc].v+t[t[b].lc].v-t[t[c].lc].v-t[t[d].lc].v;
//	cerr << b << ' ' << t[b].v << endl;
	if (k<=x)
		return _query(t[a].lc,t[b].lc,t[c].lc,t[d].lc,l,mid,k);
	else
		return _query(t[a].rc,t[b].rc,t[c].rc,t[d].rc,mid+1,r,k-x);
}

void dfs(int u,int fa)
{
	int tv;
	h[u]=_inc(h[fa],1,cnt,v[u],1);
//	cerr << t[h[u]].v << ' ' << u << "sdf\n";
	dep[u]=dep[fa]+1;
	jump[u][0]=fa;
	for (int i=1;jump[u][i-1];i++)
		jump[u][i]=jump[jump[u][i-1]][i-1];
	for (int i=_head[u];~i;i=_next[i])
	{
		tv=_node[i];
		if (tv==fa)
			continue;
		dfs(tv,u);
	}
	return ;
}

int LCA(int x,int y)
{
	if (dep[x]<dep[y])
		swap(x,y);
	int k=dep[x]-dep[y];
	for (int i=16;dep[x]!=dep[y];i--)
		if ((1<<i)&k)
			x=jump[x][i];
	if (x==y)
		return x;
	for (int i=16;jump[x][0]!=jump[y][0];i--)
		if (jump[x][i]!=jump[y][i])
			x=jump[x][i],y=jump[y][i];
	return jump[x][0];
}

int main()
{
	int u,tv,k;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]),p[i]=i;
	sort(p+1,p+1+n,_cmp);
	for (int i=1;i<=n;i++)
	{
		while (i<n && v[p[i]]==v[p[i+1]])
			v[p[i]]=cnt,i++;
		x[cnt]=v[p[i]];
		v[p[i]]=cnt++;
	}
	cnt--;
	_build(1,cnt);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&tv);
		_connect(u,tv);
		_connect(tv,u);
	}
	dfs(1,0);
	int ans=0,lca;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&u,&tv,&k);
		u^=ans;
		lca=LCA(u,tv);
	//	cerr << u << ' ' << lca << ' ' << tv  << endl;
		ans=x[_query(h[u],h[tv],h[lca],h[jump[lca][0]],1,cnt,k)];
		printf("%d\n",ans);
	}
	return 0;
}