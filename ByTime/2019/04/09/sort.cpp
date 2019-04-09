// Date      : 2019-04-09 08:31:44
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

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
}IO;

const int MAXK = 32,
		  MAXN = 1000009;

int f[2][MAXK];
int a[MAXN];
int n,q;

inline void Add(int v,int i) {if (!v) return ;v=LOG2(v),f[((a[i]&(1<<v))==0)][v]++;}
inline void Del(int v,int i) {if (!v) return ;v=LOG2(v),f[((a[i]&(1<<v))==0)][v]--;}
inline int GetAns()
{
	int ans=0;
	for (int i=0;i<=30;i++)
	{
		if (f[0][i] && f[1][i])
			return -1;
		ans|=(f[1][i]!=0)*(1<<i);
	}
	return ans;
}

int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	int x,y;
	IO.scan(n);
	for (int i=1;i<=n;i++)
		IO.scan(a[i]);
	for (int i=2;i<=n;i++)
		Add(a[i]^a[i-1],i);
//	for (int i=0;i<30;i++)
//		cerr << f[0][i] << ' ' << f[1][i] << '\n';
//	return 0;
	IO.print(GetAns(),'\n');
	IO.scan(q);
	for (int i=0;i<q;i++)
	{
		IO.scan(x,y);
		if (x!=1)
			Del(a[x]^a[x-1],x);
		if (x!=n)
			Del(a[x+1]^a[x],x+1);
		a[x]=y;
		if (x!=1)
			Add(a[x]^a[x-1],x);
		if (x!=n)
			Add(a[x+1]^a[x],x+1);
		IO.print(GetAns(),'\n');
	}
	return 0;
}