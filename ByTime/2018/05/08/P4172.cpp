#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 1009,
		  MAXM = MAXN*MAXN,
		  MAXNM= MAXN+MAXM,
		  MAXQ = 100009,
		  INF  = 1e9+9;

int n,m,q;
int a[MAXM+MAXQ],b[MAXM+MAXQ],k[MAXM+MAXQ];
int val[MAXNM],ans[MAXM+MAXQ];
int mp[MAXN][MAXN];
bool f[MAXN][MAXN];

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

int main()
{
	int x,y,z;
	bool flag;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if (x>y)
			swap(x,y);
		mp[x][y]=z;
	}
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d",&k[i],&a[i],&b[i]);
		if (a[i]>b[i])
			swap(a[i],b[i]);
		if (k[i]==2)
			f[a[i]][b[i]]=1;
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (!f[i][j] && mp[i][j])
				k[q]=2,a[q]=i,b[q++]=j;
	int u,v,w;
	for (int i=q-1;~i;i--)
	{
		u=a[i],v=b[i];
		if (k[i]==1)
		{
			w=lct.Select(u,v);
			ans[i]=val[w];
		}
		else
		{
			val[i+n]=mp[u][v];
			flag=1;
			if (lct.Find(u,v))
			{
				w=lct.Select(u,v);
				if (val[w]>val[i+n])
					lct.Cut(a[w-n],w),lct.Cut(w,b[w-n]);
				else
					flag=0;
			}
			if (flag)
				lct.Link(u,i+n),lct.Link(i+n,v);
			ans[i]=-1;
		}
	}
	for (int i=0;i<q;i++)
		if (ans[i]!=-1)
			printf("%d\n",ans[i]);
	return 0;
}
