#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 30009;

struct LCT
{
	int C[MAXN][2];
	int fa[MAXN];
	long long sum[MAXN];
	int val[MAXN],Max[MAXN],Min[MAXN];
	bool rev[MAXN];

	inline bool Isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	inline bool Child(int u) {return C[fa[u]][1]==u;}
	inline void Down(int u)
	{
		if (!rev[u]) return ;
		if (C[u][0]) rev[C[u][0]]^=1;
		if (C[u][1]) rev[C[u][1]]^=1;
		rev[u]=0;
		swap(C[u][0],C[u][1]);
		return ;
	}
	inline void Up(int u)
	{
		Max[u]=Min[u]=sum[u]=val[u];
		if (C[u][0]) sum[u]+=sum[C[u][0]],Max[u]=max(Max[u],Max[C[u][0]]),Min[u]=min(Min[u],Min[C[u][0]]);
		if (C[u][1]) sum[u]+=sum[C[u][1]],Max[u]=max(Max[u],Max[C[u][1]]),Min[u]=min(Min[u],Min[C[u][1]]);
		return ;
	}
	void Pushdown(int u)
	{
		if (!Isroot(u)) Pushdown(fa[u]);
		Down(u);
	}
	void Pushup(int u)
	{
		Up(u);
		if (!Isroot(u)) Pushup(fa[u]);
	}
	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], t = Child(u);
		if (!Isroot(v))
			C[w][Child(v)] = u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Up(v);
		return ;
	}
	void Splay(int u)
	{
		int v;
		Pushdown(u);
		while (!Isroot(u))
		{
			v=fa[u];
			if (!Isroot(v))
				Rotate(Child(v)^Child(u)?u:v);
			Rotate(u);
		}
		Up(u);
	}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			C[u][1]=t;
			t=u;
			u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		rev[u]^=1;
	}
	long long Asksum(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		return sum[v];
	}
	int AskMax(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		return Max[v];
	}
	void Update(int u,int v)
	{
		Splay(u);
		val[u]=v;
		Up(u);
		return ;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		fa[u]=v;
		Splay(u);
		return ;
	}
};

int n,q,x,y;
char s[10];
LCT lct;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		lct.Link(x,y);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		lct.Update(i,x);
	}
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%s%d%d",s,&x,&y);
		if (s[1]=='M')
			printf("%d\n",lct.AskMax(x,y));
		if (s[1]=='S')
			printf("%lld\n",lct.Asksum(x,y));
		if (s[1]=='H')
			lct.Update(x,y);
	}
	return 0;
}