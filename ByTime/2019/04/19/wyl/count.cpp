// Date      : 2019-04-19 11:27:37
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

const int MAXN = 100009,
		  MOD  = 998244353;

int cnt[MAXN];
int a[MAXN],b[MAXN],c[MAXN];
int n,m,k;

int Add(const int &x,const int &y){return x+y>=MOD?x+y-MOD:x+y;}
int Mul(const int &x,const int &y){return 1ll*x*y%MOD;}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return ans;
}

void Force(int *a,int *b,int k)
{
	if (k==1)
	{
		for (int i=1;i<=n;i++)
			b[i]=a[i];
		return ;
	}
	Force(a,b,k/2);
	fill(c+1,c+n+1,0);
	for (int i=1;i<=n;i++)
		for (int d=1;i*d<=n;d++)
			c[i*d]=Add(c[i*d],Mul(b[i],b[d]));
	for (int i=1;i<=n;i++)
		b[i]=c[i];	
	if (k&1)
	{
		fill(c,c+n+1,0);
		for (int i=1;i<=n;i++)
			for (int d=1;i*d<=n;d++)
				c[i*d]=Add(c[i*d],Mul(b[i],a[d]));
		for (int i=1;i<=n;i++)
			b[i]=c[i];		
	}
	return ;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	IO.scan(n,m,k);
	for (int i=1;i<=n;i++)
		for (int d=1;i*d<=n;d++)
			cnt[i*d]++;
	for (int i=1;i<=n;i++)
		a[i]=cnt[i];
	Force(a,b,m);
	int ans=0;
	for (int i=1;i<=n;i++)
		ans=Add(ans,Mul(qpow(i,k),b[i]));
	IO.print((ans%MOD+MOD)%MOD,'\n');
	return 0;
}
