#include <bits/stdc++.h>

using namespace std;
/*
struct LCT
{
	int C[MAXN][2];
	int rev[MAXN];
	int fa[MAXN],Max[MAXN];
	bool Child(int u) {return C[fa[u]][1]==u;}
	bool isroot(int u) {return (C[fa[u]][0]!=u && C[fa[u]][1]!=u);}
	void Down(int u)
	{
		if (!rev[u]) return ;
		rev[C[u][0]]^=1;
		rev[C[u][1]]^=1;
		rev[u]=0;
		swap(C[u][0],C[u][1]);
		return ;
	}
	void Pushup(int u)
	{
		Max[u]=max(Max[C[u][0]],Max[C[u][1]]);
		return ;
	}
	void Push(int u)
	{
		if (!isroot(u))
			Push(fa[u]);
		Down(u);
	}
	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], t = Child(u);
		if (!isroot(v))
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
		while (!isroot(u))
		{
		//	cerr << isroot(u) << ' ' << C[fa[u]][0] << ' ' << C[fa[u]][1] << '\n';
			v=fa[u];
		//	cerr << u << ' ' << v << endl;
			if(!isroot(v))
			{
				if (Child(u)==Child(v))
					Rotate(v);
				else
					Rotate(u);
			}
		//	for (int sss=0;sss<1000000000;sss++) sss+=(3%2)-1;
			Rotate(u);
		}
		Pushup(u);
		return ;
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
	//	cerr << '\n';
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		rev[u]^=1;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		fa[u]=v;
		Splay(u);
	}
	int Find(int u)
	{
		Access(u);Splay(u);
		while (C[u][0])
			u=C[u][0];
		return u;
	}
	void Cut(int u,int v)
	{
		Makeroot(u);
		Access(v);
	//	cerr << "root\n";
		Splay(v);
		C[v][0]=fa[u]=0;
	}
};
*/
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
	{
		scanf("%d")
	}
}