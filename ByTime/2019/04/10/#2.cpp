// Date      : 2019-04-10 09:27:23
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
		  MAXN = 200009;
const int prt[2]={332748118,3};

int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
int Wn[2][24];
int n;

inline int Mul(const int &a,const int &b){return 1ll*a*b%MOD;}
inline int Add(const int &a,const int &b){return (a+b)%MOD;}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return ans;
}

void init()
{
	int t=MOD-1;
	for (int i=0;i<=23;i++)
	{
		Wn[0][i]=qpow(prt[0],t/(1<<i));
		Wn[1][i]=qpow(prt[1],t/(1<<i));
	}
	return ;
}

void ntt(int n,int *a,int type)
{
	for (int i=0,j=0;i<n;i++)
	{
		if (i>j)
			swap(a[i],a[j]);
		for (int l=(n>>1);(j^=l)<l;l>>=1);
	}
	int wn,x,y;
	for (int mid=1,midt=0;mid<n;mid<<=1,midt++)
	{
		wn=Wn[type==1][midt+1];
		for (int i=0;i<n;i+=(mid<<1))
			for (int j=i,w=1;j<i+mid;j++,w=Mul(w,wn))
			{
				x=a[j],y=Mul(a[j+mid],w);
				a[j]=Add(x,y),a[j+mid]=Add(x,MOD-y);
			}
	}
	if (type==1)
		return ;
	int inv=qpow(n,MOD-2);
	for (int i=0;i<n;i++)
		a[i]=Mul(a[i],inv);
	return ;
}

int GLOBAL_n;

void polynomial_inverse(int n,int *a,int *b,int *c)
{
	if (n==1)
	{
		b[0]=qpow(a[0],MOD-2);
		return ;
	}
	int h=(n+1)>>1;
	int len=1;
	while (len<2*n)
		len<<=1;
	polynomial_inverse(h,a,b,c);
	fill(b+h,b+len,0);
	copy(a,a+n,c);
	fill(c+n,c+len,0);
	ntt(len,c,1);
	ntt(len,b,1);
	// if (n==GLOBAL_n)
		cerr << len << '\n';
	for (int i=0;i<len;i++)
	{
		// if (n==GLOBAL_n)
			cerr << c[i] << ' ' << b[i] << ' ';
		b[i]=((2ll-1ll*c[i]*b[i])%MOD+MOD)*b[i]%MOD;
		cerr << b[i] << ' ';
	}
	cerr << '\n';
	ntt(len,b,-1);
	return ;
}

void polynomial_sqrt(int n,int *a,int *b,int *c,int *d)
{
	if (n==1)
	{
		assert(a[0]==1);
		b[0]=1;
	//	c[0]=1;
		return ;
	}
	int h=(n+1)>>1;
	int len=1;
	while (len<2*n)
		len<<=1;
	polynomial_sqrt(h,a,b,c,d);
	for (int i=0;i<n;i++)
		cerr << b[i]  << ' ';
	cerr << "\n**\n";
	fill(b+h,b+len,0);
	fill(c,c+len,0);
	GLOBAL_n=n;
	polynomial_inverse(n,b,c,d);
	fill(c+n,c+len,0);
	copy(a,a+n,d);
	fill(d+n,d+len,0);
	ntt(len,d,1);
	ntt(len,c,1);
	ntt(len,b,1);
	int inv2=qpow(2,MOD-2);
	for (int i=0;i<len;i++)
	{
		b[i]=Mul(Add(Mul(b[i],b[i]),d[i]),Mul(inv2,c[i]));
//		c[i]=Add(Mul(2,c[i]),MOD-Mul(b[i],Mul(c[i],c[i])));
	}
	ntt(len,b,-1);
	ntt(len,c,-1);
//	polynomial_inverse(n,b,c,d);
	cerr << n << " : ";
	for (int i=0;i<len;i++)
		cerr << c[i] << ' ';
	cerr << '\n';
//	fill(c+n,c+len,0);
	return ;
}

int main()
{
//	freopen("P5245.in","r",stdin);
//	freopen("P5245.out","w",stdout);
	IO.scan(n);
	for (int i=0;i<n;i++)
		IO.scan(a[i]);
	init();
	polynomial_sqrt(n,a,b,c,d);
	for (int i=0;i<n;i++)
		IO.print(b[i],' ');
	IO.println();
	return 0;
}