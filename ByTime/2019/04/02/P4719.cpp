// Date      : 2019-03-31 20:08:45
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>
#include <initializer_list>

using namespace std;

const int INF  = 1000000009,
		  MAXN = 100009;


class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
public:
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
	inline void putchar(char c){(wp-wbuf==100000)?(flush()):(void)0;*wp++=c;}
	template<typename Number> void print(Number x)
	{
		if (x<0)
			putchar('-'),x=-x;
		if (x>9)
			print(x/10);
		putchar(x%10+48);
	}
	template<typename Number> void scan(Number &x)
	{
		bool f=0;x=0;char c=getchar();
		while (!isdigit(c))
			f|=(c=='-'),c=getchar();
		do {x=x*10+c-48,c=getchar();}
			while (isdigit(c));
		x=(f?x*-1:x);
		return ;
	}
	inline void println(){putchar('\n');}
	#if __cplusplus >= 201103L
		template<typename Number,typename... Numbers>
		inline void print(Number x,Numbers... X) {print(x),putchar(' '),print(X...);}
		template<typename Number,typename... Numbers>
		inline void scan(Number &x,Numbers &... X) {scan(x),scan(X...);}
	#endif
}IO;

template<int n,int m>
struct Matrix
{
	int v[n][m];
	inline void Clear()
	{
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				v[i][j]=-INF;
		return ;
	}
	Matrix(){Clear();}
	Matrix(initializer_list<int> l)
	{
		assert(l.size()<=n*m);
		auto t=l.begin();
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++,t++)
				v[i][j]=*t;
	}
	void Out()
	{
		for (int i=0;i<n;i++,cerr<<'\n')
			for (int j=0;j<m;j++)
				cerr << v[i][j] << ' ';
		cerr << '\n';
	}
};

template<int n,int m,int k>
Matrix<n,k> operator *(const Matrix<n,m> &a,const Matrix<m,k> &b)
{
	Matrix<n,k> ans;
	for (int i=0;i<n;i++)
		for (int j=0;j<k;j++)
			for (int p=0;p<m;p++)
				ans.v[i][j]=max(ans.v[i][j],a.v[i][p]+b.v[p][j]);
	return ans;
}

const Matrix<1,2> ZERO = {0,0};
const Matrix<2,2> ONE  = {0,-INF,-INF,0};

int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
Matrix<2,2> g[MAXN];
int f[MAXN][2];
int rw[MAXN],w[MAXN],a[MAXN],siz[MAXN],son[MAXN];
int top[MAXN],bot[MAXN],dep[MAXN],fa[MAXN];
int n,m,tim=0,fp=0;

struct SegmentTree
{
	Matrix<2,2> t[MAXN*4];
	inline void Up(int u){t[u]=t[u<<1]*t[u<<1|1];}
	void Build(int u,int l,int r)
	{
		if (l==r)
		{
			t[u]=g[rw[l]];
			return ;
		}
		int mid=(l+r)>>1;
		Build(u<<1,l,mid);
		Build(u<<1|1,mid+1,r);
		Up(u);
		return ;
	}
	void Modify(int u,int l,int r,int p,const Matrix<2,2> &w)
	{
		if (l==r)
		{
			t[u]=w;
			return ;
		}
		int mid=(l+r)>>1;
		if (p<=mid)
			Modify(u<<1,l,mid,p,w);
		else
			Modify(u<<1|1,mid+1,r,p,w);
		Up(u);
		return ;
	}
	Matrix<2,2> Query(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
			return t[u];
		int mid=(l+r)>>1;
		auto ans=ONE;
		if (al<=mid)
			ans=ans*Query(u<<1,l,mid,al,ar);
		if (ar>mid)
			ans=ans*Query(u<<1|1,mid+1,r,al,ar);
		return ans;
	}
};

SegmentTree ST;

inline Matrix<2,2> Query(int u){return ST.Query(1,1,n,w[u],w[bot[u]]);}
inline int GetAns(int u){return (ZERO*Query(u)).v[0][0];}

void Update(int u,int val)
{
	Matrix<2,2> od,nw;
	g[u].v[1][0]+=val-a[u];
	a[u]=val;
	while (top[u]!=1)
	{
		od=Query(top[u]);
		ST.Modify(1,1,n,w[u],g[u]);
		nw=Query(top[u]);
		u=fa[top[u]];
		g[u].v[0][1]=g[u].v[0][0]+=max(nw.v[0][0],nw.v[1][0])-max(od.v[0][0],od.v[1][0]);
		g[u].v[1][0]+=nw.v[0][0]-od.v[0][0];
	}
	ST.Modify(1,1,n,w[u],g[u]);
	return ; 
}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs1(int u)
{
	int v;
	dep[u]=dep[fa[u]]+1;
	siz[u]=1;
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

int dfs2(int u,int tp)
{
	w[u]=++tim;
	rw[w[u]]=u;
	top[u]=tp;
	if (son[u])
		bot[u]=dfs2(son[u],top[u]);
	else
		bot[u]=u;
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u] || v==son[u])
			continue;
		dfs2(v,v);
	}
	return bot[u];
}

void dfs3(int u)
{
	int v;
	f[u][0]=0,f[u][1]=a[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		dfs3(v);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
	g[u].v[0][1]=g[u].v[0][0]=f[u][0]-max(f[son[u]][0],f[son[u]][1]);
	g[u].v[1][0]=f[u][1]-f[son[u]][0];
	g[u].v[1][1]=-INF;
	return ;
}

int main()
{
	// freopen("P4719.in","r",stdin);
	// freopen("P4719.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	IO.scan(n,m);
	for (int i=1;i<=n;i++)
		IO.scan(a[i]);
	for (int i=1;i<n;i++)
	{
		IO.scan(x,y);
		_connect(x,y);
		_connect(y,x);
	}
	dfs1(1);
//	cerr << "f**k1\n";
	dfs2(1,1);
//	cerr << "f**k2\n";
	dfs3(1);
//	cerr << "f**k3\n";
	ST.Build(1,1,n);
//	for (int i=1;i<=n;i++)
//		cerr << i << ' ' << bot[i] << ' ' << w[i] << '\n';
		// Query(1).Out();
	int ans=0;
	for (int i=0;i<m;i++)
	{
		IO.scan(x,y);
	//	x^=ans;
		Update(x,y);
	//	(g[1]*g[1]).Out();
	//	Query(1).Out();
	//	cerr << bot[1] << '\n';
		IO.print(ans=GetAns(1));
		IO.println();
	}
	return 0;
}