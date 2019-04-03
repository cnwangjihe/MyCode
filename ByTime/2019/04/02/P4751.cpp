// Date      : 2019-03-31 20:08:45
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int INF  = 1000000009,
		  MAXN = 1000009;

class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
public:
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):(void)0;*wp++=c;}
	#endif
	
	template<typename Number> void print(Number x)
	{
		_print(x);
		#ifdef DEBUG
			flush();
		#endif
	}
	inline void prints(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void prints(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	template<typename Number> void _print(Number x)
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
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
}IO;

template<int n,int m>
struct Matrix
{
	int v[n][m];
	int * operator[](int i) {return v[i];}
	const int * operator[](int i) const{return v[i];}
	inline void Clear()
	{
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				v[i][j]=-INF;
		return ;
	}
	Matrix(){Clear();}
	#if __cplusplus >= 201103L
		Matrix(initializer_list<int> l)
		{
			assert(l.size()<=n*m);
			auto t=l.begin();
			for (int i=0;i<n;i++)
				for (int j=0;j<m;j++,t++)
					v[i][j]=*t;
		}
	#else
		#warning Please use c++11 to enable all features of Matrix
	#endif
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
				ans[i][j]=max(ans[i][j],a[i][p]+b[p][j]);
	return ans;
}

Matrix<2,2> operator *(const Matrix<2,2> &a,const Matrix<2,2> &b)
{
	Matrix<2,2> ans;
    ans[0][0]=max(a[0][0]+b[0][0],a[0][1]+b[1][0]);
    ans[0][1]=max(a[0][0]+b[0][1],a[0][1]+b[1][1]);
    ans[1][0]=max(a[1][0]+b[0][0],a[1][1]+b[1][0]);
    ans[1][1]=max(a[1][0]+b[0][1],a[1][1]+b[1][1]);
	return ans;
}

const Matrix<1,2> ZERO = {0,0};
const Matrix<2,2> ONE  = {0,-INF,-INF,0};

int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
Matrix<2,2> g[MAXN],t[MAXN];
int f[MAXN][2];
int rw[MAXN],w[MAXN],a[MAXN],siz[MAXN],son[MAXN];
int top[MAXN],bot[MAXN],dep[MAXN],fa[MAXN];
int C[MAXN][2];
int s[MAXN],b[MAXN];
int n,m,tim=0,fp=0,cnt=0,root;

inline void Up(int u) {t[u]=t[C[u][0]]*g[u]*t[C[u][1]];}

int Build(int l,int r)
{
	if (l>r)
		return 0;
	int x=(s[l-1]+s[r]+1)/2,L=l-1,R=r;
	while (L+1<R)
	{
		int mid=(L+R)>>1;
		if (s[mid]>=x)
			R=mid;
		else
			L=mid;
	}
	int u=b[R];
	fa[C[u][0]=Build(l,R-1)]=u;
	fa[C[u][1]=Build(R+1,r)]=u;
	Up(u);
	return u;
}

inline int GetAns(int u){return (ZERO*t[u])[0][0];}
inline bool Isroot(int u){return !(C[fa[u]][0]==u || C[fa[u]][1]==u);}

void Update(int u,int val)
{
	Matrix<2,2> od,nw;
	g[u][1][0]+=val-a[u];
	a[u]=val;
	int v;
	while (u)
	{
		v=fa[u];
		if (Isroot(u))
			g[v][0][1]=g[v][0][0]-=max(t[u][0][0],t[u][1][0]),g[v][1][0]-=t[u][0][0];
		Up(u);
		if (Isroot(u))
			g[v][0][1]=g[v][0][0]+=max(t[u][0][0],t[u][1][0]),g[v][1][0]+=t[u][0][0];
		u=v;
	}
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
	g[u][0][1]=g[u][0][0]=f[u][0]-max(f[son[u]][0],f[son[u]][1]);
	g[u][1][0]=f[u][1]-f[son[u]][0];
	g[u][1][1]=-INF;
	if (top[u]==u)
	{
		int cnt=0;
		for (int j=u;j;j=son[j])
			b[++cnt]=j,s[cnt]=s[cnt-1]+siz[j]-siz[son[j]];
		int tmp=fa[u];
		fa[root=Build(1, cnt)]=tmp;
	}
	return ;
}

int main()
{
//	freopen("P4751.in","r",stdin);
//	freopen("P4751.out","w",stdout);
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
	for (int i=0;i<=n;i++)
		t[i]=ONE;
	dfs1(1);
//	cerr << "f**k1\n";
	dfs2(1,1);
//	cerr << "f**k2\n";
	dfs3(1);
	IO.prints("f**k");
//	cerr << "f**k3\n";
//	for (int i=1;i<=n;i++)
//		cerr << i << ' ' << bot[i] << ' ' << w[i] << '\n';
//		t[i].Out();
	int ans=0;
	for (int i=0;i<m;i++)
	{
		IO.scan(x,y);
	//	x^=ans;
		Update(x,y);
	//	(g[1]*g[1]).Out();
	//	Query(1).Out();
	//	cerr << bot[1] << '\n';
		IO.print(ans=GetAns(root));
		IO.println();
	}
	return 0;
}