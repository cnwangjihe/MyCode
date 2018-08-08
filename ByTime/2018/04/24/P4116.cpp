#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 100009;

struct LCT
{
	bool Val[MAXN],Rev[MAXN];
	int Siz[MAXN],fa[MAXN];
	int C[MAXN][2];
	bool Child(int u) {return C[fa[u]][1]==u;}
	bool Isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	void Down(int u)
	{
		if (!Rev[u])
			return ;
		swap(C[u][0],C[u][1]);
		Rev[C[u][0]]^=1;
		Rev[C[u][1]]^=1;
		Rev[u]^=1;
		return ;
	}
	void Up(int u)
	{
		Siz[u]=Siz[C[u][0]]+Siz[C[u][1]]+Val[u];
		return ;
	}
	void Push_down(int u)
	{
		if (!Isroot(u))
			Push_down(fa[u]);
		Down(u);
		return ;
	}
	void Rotate(int u)
	{
		int v=fa[u],w=fa[v],t=Child(u);
		if (!Isroot(v))
			C[w][Child(v)]=u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Up(v);Up(u);
	}
	void Splay(int u)
	{
		int v;
		Push_down(u);
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
		return ;
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
		Rev[u]^=1;
		return ;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		fa[u]=v;
		return ;
	}
	void Update(int u)
	{
		Splay(u);
		Val[u]^=1;
		Up(u);
		return ;
	}
	int Query(int u)
	{
		Access(u);
		Splay(u);
		while (1)
		{
		//	cerr << u << ' ';
			if (!Siz[u])
				return -1;
			if (Val[u] && !Siz[C[u][0]])
				return u;
			u=(Siz[C[u][0]])?C[u][0]:C[u][1];
		}
		return -2;
	}
};

LCT lct;
int n,q;

int main()
{
	int a,b;
	scanf("%d%d",&n,&q);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		lct.Link(a,b);
	}
	lct.Makeroot(1);
	for (int i=0;i<q;i++)
	{
		scanf("%d%d",&a,&b);
		if (a==0)
			lct.Update(b);
		else
			printf("%d\n",lct.Query(b));
	//	cerr << '\n';
	}
	return 0;
}