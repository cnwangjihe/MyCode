#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100009;

int n,m;
int a,b;

struct LCT
{
	bool Rev[MAXN];
	int Siz[MAXN],fa[MAXN],Val[MAXN];
	int C[MAXN][2];
	inline bool Isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	inline bool Child(int u) {return C[fa[u]][1]==u;}
	inline void Up(int u)
	{
		Siz[u]=Siz[C[u][0]]+Siz[C[u][1]]+Val[u]+1;
		return ;
	}
	inline void Down(int u)
	{
		if (!Rev[u])
			return ;
		Rev[C[u][0]]^=1;
		Rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		Rev[u]=0;
		return ;
	}
	void Rotate(int u)
	{
		int v=fa[u],w=fa[v],t=Child(u);
		if (!Isroot(v))
			C[w][Child(v)]=u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Up(v);
		return ;
	}
	void Pushdown(int u)
	{
		if (!Isroot(u))
			Pushdown(fa[u]);
		Down(u);
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
			{
				if (Child(v)==Child(u))
					Rotate(v);
				else
					Rotate(u);
			}
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
			Val[u]+=Siz[C[u][1]]-Siz[t];
			C[u][1]=t;
			Up(u);
			t=u;
			u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		Rev[u]^=1;
		return ;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		Makeroot(v);
		fa[v]=u;
		Val[u]+=Siz[v];
		Up(u);
		return ;
	}
	void Cut(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		C[v][0]=0;
		fa[u]=0;
		return ;
	}
	long long Query(int u,int v)
	{
		Makeroot(u);
		Access(v);
		return ((long long)Val[u]+1)*((long long)Val[v]+1);
	}
}lct;

int main()
{
	char c[10];
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%s%d%d",c,&a,&b);
		if (c[0]=='A')
			lct.Link(a,b);
		else
			printf("%lld\n",lct.Query(a,b));
	}
	return 0;
}