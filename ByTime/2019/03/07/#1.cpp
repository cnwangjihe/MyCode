// Date      : 2019-03-07 10:39:31
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MAXE = MAXN*2,
		  INF  = 1000000009;

struct Heap
{
	multiset<int> data;
	inline void Erase(int v) {data.erase(data.find(v));}
	inline void Insert(int v) {data.insert(v);}
	inline int First() {return data.size()?(*data.rbegin()):-INF;}
	inline int Second() {return data.size()>1?(*(++data.rbegin())):-INF;}
};

struct LCT
{
	#define lc C[u][0]
	#define rc C[u][1]
	int C[MAXN][2];
	int fa[MAXN],Val[MAXN];
	int Lmx[MAXN],Rmx[MAXN],Mxs[MAXN],Sum[MAXN];
	Heap Chain[MAXN],Path[MAXN];
	int ans;

	inline void Clear()
	{
		ans=0;
		for (int i=0;i<MAXN;i++)
			Val[i]=0;
		for (int i=0;i<MAXN;i++)
			Lmx[i]=Rmx[i]=Mxs[i]=-INF;
		return ;
	}
	LCT(){Clear();}
	inline bool Child(int u) {return C[fa[u]][1]==u;}
	inline bool isroot(int u) {return (C[fa[u]][0]!=u && C[fa[u]][1]!=u);}
	inline void Insert(int u,int v) {Chain[u].Insert(Lmx[v]),Path[u].Insert(Mxs[v]);}
	inline void Erase(int u,int v) {Chain[u].Erase(Lmx[v]),Path[u].Erase(Mxs[v]);}
//	inline void Down(int u) {return ;}
	inline void Up(int u)
	{
		Sum[u]=Sum[lc]+Sum[rc]+Val[u];
		int smax=max(0,Chain[u].First()),
			L = max(smax, Rmx[lc])+Val[u],
			R = max(smax, Lmx[rc])+Val[u];
		Lmx[u]=max(Lmx[lc],Sum[lc]+R);
		Rmx[u]=max(Rmx[rc],Sum[rc]+L);
		Mxs[u]=max(Rmx[lc]+R,Lmx[rc]+L);
		Mxs[u]=max(Mxs[u],max(Mxs[lc],Mxs[rc]));
		Mxs[u]=max(Mxs[u],Path[u].First());
		Mxs[u]=max(Mxs[u],smax+Chain[u].Second()+Val[u]);
		Mxs[u]=max(Mxs[u],smax+Val[u]);
		return ;
	}
//	void Pushdown(int u)
//	{
//		if (!isroot(u))
//			Pushdown(fa[u]);
//		Down(u);
//	}

	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], c = Child(u);
		if (!isroot(v))
			C[w][Child(v)]=u;
		fa[u]=w;
		C[v][c] = C[u][c ^ 1];
		if (C[v][c])
			fa[C[v][c]]=v;
		C[u][c^1]=v;fa[v] = u; Up(v);
		return ;
	}
	void Splay(int u)
	{
	//	Pushdown(u);

		for( ;!isroot(u); Rotate(u))
			if(!isroot(fa[u]))
				Rotate(Child(fa[u])==Child(u)?fa[u]:u);
		Up(u);
		return ;
	}
	void Access(int u)
	{
		int t=0,tu=u;
		while (u)
		{
			Splay(u);
			if (t)
				Erase(u,t);
			if(C[u][1])
				Insert(u,C[u][1]);
			C[u][1]=t;t=u,Up(u),u=fa[u];
		}
		Splay(tu);
		return ;
	}
	void Modify(int u,int w)
	{
		Access(u);
		Val[u]=w;
		Up(u);
		ans=Mxs[u];
		return ;
	}
	void Refresh(){ans=Mxs[1];}
};

LCT LCT;
int _head[MAXN],_node[MAXE],_next[MAXE];
int n,m,fp=0;

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		LCT.fa[v]=u;
		dfs(v,u);
		LCT.Insert(u,v);
	}
	LCT.Up(u);
	return ;
}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	int tn=n,x,y;
	for (int i=2;i<=tn;i++)
	{
		scanf("%d",&x),n++;
		_connect(x,n),_connect(n,x);
		_connect(n,i),_connect(i,n);
	}
	dfs(1,0);
	LCT.Refresh();
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		LCT.Modify(x+tn-1,y);
		printf("%d\n",LCT.ans);
	}
	return 0;
}
