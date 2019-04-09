// Date      : 2019-04-08 08:57:14
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
public:
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):void();*wp++=c;}
	#endif
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
		inline void print(Number x,Numbers... X) {print(x),putchar(' '),print(X...);}
		template<typename Number,typename... Numbers>
		inline int scan(Number &x,Numbers &... X) {return scan(x)+scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
}IO;

const int MAXN = 1009,
		  MOD  = 1000000007;

int v[MAXN],s[MAXN];
set<int> a[MAXN];
int n,m,q;

inline int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

int Solve()
{
	for (int i=0;i<=n;i++)
		s[i]=0;
	long long ans=0;
	int top=0;
	// int Mtop=0;
	s[0]=m+1;
	for (int i=1;i<=n;i++)
	{
		s[top+1]=-1;
		int j;
		for (j=1;j<=top && a[i].count(s[j]);j++);
		top=j-1;
		while (1)
		{
			auto p=a[i].upper_bound(s[top+1]);
			if (p==a[i].end())
				return -1;
			if (*p<s[top])
			{
				s[++top]=*p;
				break;
			}
			if (!top)
				return -1;
			top--;
		}
		v[top]=(v[top-1]+qpow(2,s[top]))%MOD;
		// cerr << s[top] << ' ' << v[top] << '\n';
		// Mtop=max(top,Mtop);
		ans=(ans+v[top])%MOD;
	}
	// cerr << Mtop << '\n';
	return ans;
}

int main()
{
	freopen("price.in","r",stdin);
	freopen("price.out","w",stdout);
	int opt,x,y;
	IO.scan(n,m,q);
	for (int i=0;i<q;i++)
	{
		IO.scan(opt);
		if (opt-1)
			IO.print(Solve(),"\n");
		else
		{
			IO.scan(x,y);
			if (a[x].count(m-y))
				a[x].erase(m-y);
			else
				a[x].insert(m-y);
		}
	}
	return 0;
}