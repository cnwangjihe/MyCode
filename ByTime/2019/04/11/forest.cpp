// Date      : 2019-04-11 09:34:37
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
	IO(){}
	struct ObjectCreator{ObjectCreator(){IO::GetInstance();}};
	static ObjectCreator _oc;
public:
	static IO &GetInstance(){static IO Instance;return Instance;}
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):void();*wp++=c;}
	#endif
	inline void print(char c) {putchar(c);}
	inline void print(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void print(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline int scan(char *s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s[n++]=c,c=getchar();}
			while (check(c));
		s[n]='\0';
		return n;
	}
	inline int scan(string &s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		s="";
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s+=c,c=getchar();n++;}
			while (check(c));
		return n;
	}
	template<typename Number> void print(Number x)
	{
		if (x<0)
			putchar('-'),x=-x;
		if (x>9)
			print(x/10);
		putchar(x%10+48);
	}
	template<typename Number> int scan(Number &x)
	{
		bool f=0;x=0;short c=getchar();
		while (!isdigit(c) && (~c))
			f|=(c=='-'),c=getchar();
		if (!~c)
			return 0;
		do {x=x*10+c-48,c=getchar();}
			while (isdigit(c));
		x=(f?x*-1:x);
		return 1;
	}
	inline void println(){putchar('\n');}
	#if __cplusplus >= 201103L
		template<typename Number,typename... Numbers>
		inline void print(Number x,Numbers... X) {print(x),print(X...);}
		template<typename Number,typename... Numbers>
		inline int scan(Number &x,Numbers &... X) {return scan(x)+scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
};

IO &IO=IO::GetInstance();

const int MAXN = 200009,
		  INF  = 1000000009;

struct LCT
{
	int C[MAXN][2];
	int fa[MAXN];
	int lmax[MAXN],rmax[MAXN],smax[MAXN],size[MAXN];
	bool rev[MAXN];
	multiset<int> sub[MAXN];
	LCT(){lmax[0]=rmax[0]=smax[0]=-INF;}
	inline bool Child(const int &u){return C[fa[u]][1]==u;}
	inline bool Isroot(const int &u){return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	inline int Get(multiset<int> *s){return s->rbegin()==s->rend()?0:(*(s->rbegin()));}
	inline void Up(int u)
	{
		size[u]=size[C[u][0]]+size[C[u][1]]+1;
		smax[u]=max(Get(&sub[u]),max(smax[C[u][0]],smax[C[u][1]]));
		lmax[u]=max(size[C[u][0]]+max(Get(&sub[u]),size[C[u][1]]),max(lmax[C[u][0]],lmax[C[u][1]]+size[C[u][0]]+1));
		rmax[u]=max(size[C[u][1]]+max(Get(&sub[u]),size[C[u][0]]),max(rmax[C[u][1]],rmax[C[u][0]]+size[C[u][1]]+1));
		return ;
	}
	inline void Down(int u)
	{
		if (!rev[u])
			return ;
		rev[u]=0;
		rev[C[u][0]]^=1,rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		swap(lmax[u],rmax[u]);
		return ;
	}
	void PushDown(int u)
	{
		if (!Isroot(u))
			PushDown(fa[u]);
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
		Up(v);Up(u);
		return ;
	}
	void Splay(int u)
	{
		int v;
		PushDown(u);
		while (!Isroot(u))
		{
			v=fa[u];
			if (!Isroot(v))
				Rotate(Child(v)==Child(u)?v:u);
			Rotate(u);
		}
		return ;
	}
	inline void Add(int v,int u){sub[v].insert(lmax[u]+1),Up(v);}
	inline void Del(int v,int u){cerr<<'!';sub[v].erase(sub[v].find(lmax[u]+1));cerr<<'!';Up(v);}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			cerr << "^";
			if (C[u][1])
				Add(u,C[u][1]);
			cerr << "$";
			if (t)
				Del(u,t);
			cerr << "#";
			C[u][1]=t;
			Up(u);
			t=u,u=fa[u];
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
		Makeroot(u);Makeroot(v);
		fa[u]=v;
		Splay(u);
		Add(v,u);
		return ;
	}
	int Query(int a,int b)
	{
		Makeroot(a);
		Access(b);
		Splay(b);
		return max(size[b]+smax[b]-2,size[b]-1);
	}
	int QueryDis(int a,int b)
	{
		Makeroot(a);
		cerr << "&";
		Access(b);
		cerr << "&";
		Splay(b);
		return size[b]-1;
	}
}LCT;

int x,y,n;

void Renew(int a)
{
	int d1=LCT.QueryDis(x,y);
	cerr << d1;
	int d2=LCT.QueryDis(x,a);
	cerr << d2;
	int d3=LCT.QueryDis(y,a);
	cerr << d3;
	int t=max(d1,max(d2,d3));
	if (d1==t)
		return ;
	if (d2==t)
		return void(y=a);
	if (d3==t)
		return void(x=a);
	return ;
}

int main()
{
//	freopen("forest.in","r",stdin);
//	freopen("forest.out","w",stdout);
	int task,a,ans=0;
	x=y=1;
	IO.scan(task,n);
	for (int i=2;i<=n;i++)
	{
		IO.scan(a);
	//	a^=ans;
		LCT.Link(i,a);
		for (int j=1;j<=i;j++)
			cerr << j << " : " << LCT.fa[j] << ' ' << LCT.C[j][0] << "  " << LCT.C[j][1] << '\n';
		Renew(i);
		IO.print(ans=LCT.Query(x,y),'\n');
	}
	return 0;
}