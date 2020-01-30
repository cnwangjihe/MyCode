// Date      : 2019-04-19 10:29:55
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

const int MAXN = 1000009;

int _head[MAXN],_next[MAXN],_node[MAXN],_val[MAXN];
int w[MAXN],rw[MAXN],dep[MAXN],siz[MAXN],val[MAXN];
long long sum[MAXN],t[MAXN];
int fp=0,n,q,tim=0;

inline void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
	int v;
	w[u]=++tim;
	rw[tim]=u;
	siz[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		dep[v]=dep[u]+1;
		val[v]=(dep[u]&1)?-_val[i]:_val[i];
		sum[v]=sum[u]+val[v];
		dfs(v);
		siz[u]+=siz[v];
	}
	return ;
}
void Add(int x,int v)
{
	for (int i=x;i<=n;i+=i&(-i))
		t[i]+=v;
	return ;
}
long long Query(int x)
{
	long long sum=0;
	for (int i=x;i;i-=i&(-i))
		sum+=t[i];
	return sum;
}

int main()
{
	freopen("equation.in","r",stdin);
	freopen("equation.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,t;
	IO.scan(n,q);
	for (int i=1;i<n;i++)
	{
		IO.scan(x,y);
		_connect(x,i+1,y);
	}
	dep[1]=1;
	dfs(1);
	for (int i=1;i<=n;i++)
		Add(i,sum[rw[i]]-sum[rw[i-1]]);
	int z;
	long long s1,s2,s;
	for (int i=0;i<q;i++)
	{
		IO.scan(t);
		if (t-1)
		{
			IO.scan(x,y);
			y=(dep[x]&1)?y:-y;
			Add(w[x],y-val[x]);
			Add(w[x]+siz[x],val[x]-y);
			val[x]=y;
		}
		else
		{
			IO.scan(x,y,z);
			s1=((dep[x]&1)?1:-1)*Query(w[x]);
			s2=((dep[y]&1)?1:-1)*Query(w[y]);
		//	cerr << s1 << ' ' << s2 << endl;
			if ((dep[x]&1)!=(dep[y]&1))
				IO.print(s1+s2==z?"inf\n":"none\n");
			else
			{
				s=((dep[x]&1)?-1:1)*(s1+s2-z);
				if (s&1)
					IO.print("none\n");
				else
					IO.print(s/2,'\n');
			}
		}
	}
	return 0;
}