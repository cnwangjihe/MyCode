// Date      : 2019-02-18 20:26:48
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P4211
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009,
		  MAXM = MAXN*2,
		  MOD  = 201314;

struct Tnode {int sum,add,cnt;Tnode(){sum=add=cnt=0;}};

struct SegmentTree
{
	Tnode t[MAXN*4];
	inline void Up(int u) {t[u].sum=t[u*2].sum+t[u*2+1].sum;}
	void Down(int u)
	{
		t[u*2].sum+=t[u].add*t[u*2].cnt;
		t[u*2+1].sum+=t[u].add*t[u*2+1].cnt;
		t[u*2].add+=t[u].add;
		t[u*2+1].add+=t[u].add;
		t[u].add=0;
		return ;
	}
	void Build(int u,int l,int r)
	{
		if (l==r)
		{
			t[u].cnt=1;
			return ;
		}
		int mid=(l+r)>>1;
		Build(u*2,l,mid);
		Build(u*2+1,mid+1,r);
		t[u].cnt=t[u*2].cnt+t[u*2+1].cnt;
		return ;
	}
	void Modify(int u,int l,int r,int al,int ar,int v)
	{
		if (al>ar)
			return ;
		if (al<=l && ar>=r)
		{
			(t[u].sum+=t[u].cnt*v)%=MOD;
			(t[u].add+=v)%=MOD;
			return ;
		}
		Down(u);
		int mid=(l+r)>>1;
		if (al<=mid)
			Modify(u*2,l,mid,al,ar,v);
		if (ar>mid)
			Modify(u*2+1,mid+1,r,al,ar,v);
		Up(u);
		return ;
	}
	int Query(int u,int l,int r,int al,int ar)
	{
		if (al>ar)
			return 0;
		if (al<=l && ar>=r)
			return t[u].sum;
		Down(u);
		int mid=(l+r)>>1,ans=0;
		if (al<=mid)
			ans+=Query(u*2,l,mid,al,ar);
		if (ar>mid)
			ans+=Query(u*2+1,mid+1,r,al,ar);
		return ans%MOD;
	}
};

SegmentTree ST;
int _head[MAXN],_next[MAXM],_node[MAXM];
int p[MAXN],ans[MAXN];
int top[MAXN],fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN],w[MAXN],rw[MAXN];
int n,m,fp=0,tim=0;
vector<pair<int,int> > q[MAXN];

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs1(int u)
{
	int v;
	siz[u]=1;
	dep[u]=dep[fa[u]]+1;
	son[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		fa[v]=u;
		dfs1(v);
		siz[u]+=siz[v];
		if (siz[v]>siz[son[u]])
			son[u]=v;
	}
	return ;
}

void dfs2(int u,int t)
{
	int v;
	w[u]=++tim;
	rw[tim]=u;
	top[u]=t;
	if (son[u])
		dfs2(son[u],t);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u] || v==son[u])
			continue;
		dfs2(v,v);
	}
	return ;
}

void Modify(int a,int b,int v)
{
	while (top[a]!=top[b])
	{
		if (dep[top[a]]<dep[top[b]])
			swap(a,b);
		ST.Modify(1,1,n,w[top[a]],w[a],v);
		a=fa[top[a]];
	}
	if (dep[a]<dep[b])
		swap(a,b);
	ST.Modify(1,1,n,w[b],w[a],v);
	return ;
}

int Query(int a,int b)
{
	int ans=0;
	while (top[a]!=top[b])
	{
		if (dep[top[a]]<dep[top[b]])
			swap(a,b);
		(ans+=ST.Query(1,1,n,w[top[a]],w[a]))%=MOD;
		a=fa[top[a]];
	}
	if (dep[a]<dep[b])
		swap(a,b);
	(ans+=ST.Query(1,1,n,w[b],w[a]))%=MOD;
	return ans;
}

int main()
{
//	freopen("P4211.in","r",stdin);
//	freopen("P4211.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,l,r;
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&x),x++;
		_connect(i,x);
		_connect(x,i);
	}
	ST.Build(1,1,n);
	dfs1(1);
	dfs2(1,1);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l,&r,&p[i]),l++,r++,p[i]++;
		q[l-1].push_back(make_pair(i,-1));
		q[r].push_back(make_pair(i,1));
	}
	for (int i=1;i<=n;i++)
	{
		Modify(1,i,1);
		for (int j=0;j<q[i].size();j++)
			ans[q[i][j].first]+=q[i][j].second*Query(1,p[q[i][j].first]);
	}
	for (int i=1;i<=m;i++)
		printf("%d\n",(ans[i]%MOD+MOD)%MOD);
	return 0;
}