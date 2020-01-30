// Date      : 2019-04-13 11:18:03
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

const int MOD  = 998244353,
		  MAXN = 209;

int a[1000009],b[1000009],f[MAXN];
int c[MAXN][MAXN];
int n,m;

inline int Add(const int &a,const int &b){return a+b>=MOD?a+b-MOD:a+b;}
inline int Mul(const int &a,const int &b){return 1ll*a*b%MOD;}
inline int Mod(const int &a){return a<0?a+MOD:a;}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return ans;
}

int Gauss(int a[MAXN][MAXN],int n)
{
	int id;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (abs(a[j][i])>abs(a[id][i]))
				id=j;
		if (id!=i)
			for (int j=1;j<=n;j++)
				swap(a[i][j],a[id][j]);
		if (a[i][i]==0)
			return -1;
		int inv=qpow(a[i][i],MOD-2);
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			for (int k=n;k>=i;k--)
				a[j][k]=Add(a[j][k],Mod(-Mul(Mul(a[i][k],a[j][i]),inv)));
		}
	}
	int ans=1;
	for (int i=1;i<=n;i++)
		ans=Mul(ans,a[i][i]);
	return ans;
}

int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	IO.scan(n);
	for (int i=1;i<=n;i++)
		IO.scan(f[i]),m=max(f[i],m);
	b[1]=a[1]=1;
	for (int i=2;i<=m;i++)
		a[i]=(i&1?((i>>1)&1?-1:1)*a[(i>>1)+1]:-a[i>>1]);
	for (int i=2;i<=m;i++)
		b[i]=Add(b[i-1],Mod(a[i]));
	for (int i=1;i<=n;i++) 
		for (int j=1;j<=n;j++)
			c[i][j]=b[f[__gcd(i,j)]];
	IO.print(Gauss(c,n),'\n');
	return 0;
}