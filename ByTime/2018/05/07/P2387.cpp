#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 50009,
		  MAXM = 100009,
		  MAXNM= MAXN+MAXM,
		  INF  = 1e9+9;

int n,m,ans=INF;
int val[MAXNM];

struct Tedge{int a,b,v1,v2;}e[MAXM];

struct LCT
{
	int C[MAXNM][2];
	bool Rev[MAXNM];
	int fa[MAXNM],Max[MAXNM];
	bool Isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	bool Child(int u) {return C[fa[u]][1]==u;}
	void Up(int u)
	{
		Max[u]=u;
		if (val[Max[u]]<val[Max[C[u][0]]])
			Max[u]=Max[C[u][0]];
		if (val[Max[u]]<val[Max[C[u][1]]])
			Max[u]=Max[C[u][1]];
		return ;
	}
	void Down(int u)
	{
		if (!Rev[u])
			return ;
		Rev[C[u][0]]^=1;
		Rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		Rev[u]=0;
		return ;
	}
	void Pushdown(int u)
	{
		if (!Isroot(u))
			Pushdown(fa[u]);
		Down(u);
		return ;
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
		Pushdown(u);
		int v;
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
			Up(u);
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
		Splay(u);
		fa[u]=v;
		return ;
	}
	void Cut(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		fa[u]=C[v][0]=0;
		return ;
	}
	bool Find(int u,int v)
	{
		Makeroot(v);
		Access(u);
		Splay(u);
		while (C[u][0])
			u=C[u][0];
		return u==v;
	}
	int Select(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		return Max[v];
	}
}lct;

bool _cmp(Tedge a,Tedge b) {return a.v1<b.v1;}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
		scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].v1,&e[i].v2);
	sort(e+1,e+1+m,_cmp);
	for (int i=1;i<=n;i++)
		val[i]=0;
	for (int i=n+1;i<=n+m;i++)
		val[i]=e[i-n].v2;//,cerr << e[i-n].a << ' ' << e[i-n].b << ' '<< e[i-n].v1 << ' ' << e[i-n].v2 << '\n';
	for (int i=1;i<=m;i++)
	{
		int u=e[i].a,v=e[i].b,w;
		bool f=1;
	//	cerr << lct.Find(u,v) << '\n';
		if (lct.Find(u,v))
		{
	//		cerr << "in ";
			w=lct.Select(u,v);
			if (val[w]>val[i+n])
				lct.Cut(e[w-n].a,w),lct.Cut(w,e[w-n].b);
			else
				f=0;
	//		cerr << w << endl;
		}
	//	cerr << f << ' ' << ans << ' ';
		if (f)
			lct.Link(u,i+n),lct.Link(i+n,v);
	//	cerr << lct.Find(1,n) << endl;
		if (lct.Find(1,n))
			ans=min(ans,e[i].v1+val[lct.Select(1,n)]);
	}
	printf("%d\n",ans==INF?-1:ans);
	return 0;
}
