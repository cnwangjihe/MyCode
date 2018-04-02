#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 50009,
		  MOD  = 2018;

int _head[MAXN],_next[MAXN],_node[MAXN];
int _val[MAXN],_cnt[MAXN],_sum[MAXN],_ans[MAXN];
int w[MAXN],rw[MAXN],size[MAXN],son[MAXN],fa[MAXN],dep[MAXN],top[MAXN];
int b[MAXN];
int fp=0,n,q,a,tim,len,cnt;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
}

int dfs1(int u)
{
//	cerr << u << endl;
	int v;
	dep[u]=dep[fa[u]]+1;
	size[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		fa[v]=u;
		if (dfs1(v)>size[son[u]])
			son[u]=v;
		size[u]+=size[v];
	}
	return size[u];
}

void dfs2(int u,int tp)
{
//	cerr << u << '\n';
	int v;
	w[u]=++tim;
	top[u]=tp;
	if (son[u])
	{
		dfs2(son[u],tp);
		v=son[u];
		_val[u]=(_cnt[u]*_sum[v])%MOD+(size[v]*_sum[u])%MOD;
		_val[u]%=MOD;
		_sum[u]+=_sum[v]+size[v]*b[v];
		_sum[u]%=MOD;
		_cnt[u]+=size[v];
		_ans[u]+=_val[v];
		_cnt[u]%=MOD;
		_ans[u]%=MOD;
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (fa[u]==v || son[u]==v)
			continue;
		dfs2(v,v);
		_val[u]=_cnt[u]*(_sum[v]+size[v]*b[v])%MOD+(size[v]*_sum[u])%MOD;
		_sum[u]+=_sum[v]+(size[v]*b[v])%MOD;
		_val[u]%=MOD;_sum[u]%=MOD;
	//	if (u==2) cerr << _val[u] << endl;
		_cnt[u]+=size[v];
		_ans[u]+=_val[v];
		_cnt[u]%=MOD;
		_ans[u]%=MOD;
	}
	_val[u]+=_sum[u];
	_ans[u]+=_val[u];
	_val[u]%=MOD;
	_ans[u]%=MOD;
	return ;
}
/*
void _build()
{
	for (int i=0;i<cnt;i++)
	{
		for (int j=i*len;j<(i+1)*len;j++)
		{
			sum[i]+=_val[rw[j]];
			cnt[i]+=
		}
	}
}

void Add(int a,int b,int v)
{
	while (top[a]!=top[b])
	{
		if (dep[top[a]]<dep[top[b]])
			swap(a,b);
		_add(top[a],,v);
	}
	if ()
}
*/

void Add(int a,int b,int v)
{
	int k1=0,k2=0,k3=0,k4=0;
	if (dep[a]<dep[b])
		swap(a,b);
	while (dep[a]>dep[b])
	{
		k1+=(((size[fa[a]]-size[a])*size[a])%2018)*v;
		k1%=MOD;
		k3+=k1;
		k3%=MOD;
//		cerr <<" :" <<  k1 << endl;
		_val[fa[a]]+=k1;
		_ans[fa[a]]+=k3;
		_val[fa[a]]%=MOD;
		_ans[fa[a]]%=MOD;
		a=fa[a];
	}
	while (a!=b)
	{
		k1+=(((size[fa[a]]-size[a])*size[a])%MOD)*v;
		k1%=MOD;
		k3+=k1;
		k3%=MOD;
		_val[fa[a]]+=k1;
		_ans[fa[a]]+=k3;
		_val[fa[a]]%=MOD;
		_ans[fa[a]]%=MOD;
		k2+=(long long)(size[fa[b]]-size[b])*size[b]*v;
		k2%=MOD;
		k4+=k1;
		k4%=MOD;
		_val[fa[b]]+=k2;
		_ans[fa[b]]+=k4;
		_val[fa[b]]%=MOD;
		_ans[fa[b]]%=MOD;
		a=fa[a];
		b=fa[b];
	}
	k1+=k2;
	k3+=k4;
	k1%=MOD;
	k3%=MOD;
	while (a!=1)
	{
		k3+=k1;
		k3%=MOD;
		_ans[fa[a]]+=k3;
		_val[fa[a]]+=k1;
		_val[fa[a]]%=MOD;
		_ans[fa[a]]%=MOD;
		a=fa[a];
	}
	return ;
}

int main()
{
	freopen("country.in","r",stdin);
	freopen("country.out","w",stdout);
	memset(_head,-1,sizeof _head);
	memset(_sum,0,sizeof _sum);
	scanf("%d%d",&n,&q);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b[i+1]);
		_connect(a,i+1);
	}
	len=int(sqrt(n));
	cnt=n%len?n/len+1:n/len;
	tim=0;
	size[0]=0;
	dfs1(1);
	dfs2(1,1);
	for (int i=1;i<=n;i++)
		rw[w[i]]=i;
//	for (int i=1;i<=n;i++)
//		cerr << _val[i] << ' ';
	
	char c,ch;
	int x,y,z;
	for (int i=0;i<q;i++)
	{
		do {c=getchar();}
			while (c<'A' || c>'Z');
		do {ch=getchar();}
			while (ch>='A' && ch<='Z');
		if (c=='I')
		{
			scanf("%d%d%d",&x,&y,&z);
			Add(x,y,z);
//		for (int i=1;i<=n;i++)
//			cerr << _val[i] << ' ';
		}
		else
		{
			scanf("%d",&x);
			printf("%d\n",_ans[x]%=MOD);
		}
	}
	return 0;
}
