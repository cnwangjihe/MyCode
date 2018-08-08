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
	bool Rev[MAXN];
	int Siz[MAXN],fa[MAXN],Val[MAXN];
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
		Siz[u]=Siz[C[u][0]]+Siz[C[u][1]]+Val[u]+1;
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
		Up(v);
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
			Val[u]+=Siz[C[u][1]]-Siz[t];
			C[u][1]=t;
			Up(u);
			t=u;
			u=fa[u];
		}
		return ;
	}
	void Link(int u,int v)
	{
		if (!v)
			return ;
		Access(u);Splay(u);
		fa[u]=v;
		Access(v);Splay(v);
		Val[v]+=Siz[u];
		Up(v);
		return ;
	}
	void Cut(int u)
	{
		Access(u);Splay(u);
		C[u][0]=fa[C[u][0]]=0;
		Up(u);
		return ;
	}
	int Query(int u)
	{
		Access(u);Splay(u);
		while (C[u][0]) u=C[u][0];
		Splay(u);
		return u;
	}
};

int _next[MAXN*2],_head[MAXN],_node[MAXN*2];
int fa[MAXN],col[MAXN];
LCT lct[2];
int n,m,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fat)
{
	int v;
	fa[u]=fat;
	lct[0].Link(u,fa[u]);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		dfs(v,u);
	}
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int a,b,t;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	dfs(1,n+1);
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		if (!a)
		{
			t=lct[col[b]].Query(b);
			printf("%d\n",lct[col[b]].Siz[lct[col[b]].C[t][1]]);
		}
		else
		{
			lct[col[b]].Cut(b);
			lct[col[b]^=1].Link(b,fa[b]);
		}
	}
	return 0;
}