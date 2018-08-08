#include <fstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 202009;

struct LCT
{
	int C[MAXN][2];
	int fa[MAXN],size[MAXN];
	bool rev[MAXN];
	bool Child(int u) {return C[fa[u]][1]==u;}
	bool Isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	void Down(int u)
	{
		if (!rev[u]) return ;
		if (C[u][0]) rev[C[u][0]]^=1;
		if (C[u][1]) rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		rev[u]=0;
		return ;
	}
	void Pushup(int u)
	{
		size[u]=1;
		if (C[u][0]) size[u]+=size[C[u][0]];
		if (C[u][1]) size[u]+=size[C[u][1]];
		return ;
	}
	void Push(int u)
	{
		if (!Isroot(u))
			Push(fa[u]);
		Down(u);
	}
	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], t = Child(u);
		if (!Isroot(v))
			C[w][Child(v)] = u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Pushup(v);
		return ;
	}
	void Splay(int u)
	{
		Push(u);
		int v;
		while (!Isroot(u))
		{
			v=fa[u];
			if (!Isroot(v))
				Rotate((Child(u)==Child(v))?v:u);
			Rotate(u);
		}
		Pushup(u);
	}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			C[u][1]=t;
			t=u;u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		rev[u]^=1;
		return ;
	}
	void Link(int u,int v)
	{
		Makeroot(v);
		fa[v]=u;
		Splay(v);
		return ;
	}
	void Cut(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		fa[u]=0;
		C[v][0]=0;
	}
	int Query(int u,int v)
	{
		Makeroot(v);
		Access(u);
		Splay(u);
		return size[C[u][0]];
	}
}lct;

int a[MAXN];
int n,m;

int main()
{
	int u,v,t;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		lct.Link(i,min(a[i]+i,n+1));
	}
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d",&t);
		if (t-1)
		{
			scanf("%d%d",&u,&v);
			u++;
			lct.Cut(u,min(a[u]+u,n+1));
			a[u]=v;
			lct.Link(u,min(a[u]+u,n+1));
		}
		else
		{
			scanf("%d",&u);
			printf("%d\n",lct.Query(u+1,n+1));
		}
	}
	return 0;
}
