// Date      : 2019-04-14 13:45:39
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

struct Complex {int x,y,k;Complex(int a=0,int b=0,int c=0):x(a),y(b),k(c){};};

const int MOD  = 998244353;
const int prt[2]={332748118,3};

int Wn[2][24];

inline int Mod(const int &a){return a<0?MOD+a:a;}
inline int Mul(const int &a,const int &b){return 1ll*a*b%MOD;}
inline int Add(const int &a,const int &b){return a+b>MOD?a+b-MOD:a+b;}
inline Complex Mul(const Complex &a,const Complex &b){return Complex(Add(Mul(a.x,b.x),Mul(max(a.k,b.k),Mul(a.y,b.y))),Add(Mul(a.x,b.y),Mul(a.y,b.x)),max(a.k,b.k));}

inline Complex qpow(Complex a,int k)
{
	Complex ans=Complex();bool f=0;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=f?Mul(ans,a):(f=1,a);
	return ans;
}

inline int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return ans;
}

int modsqrt(int a)
{
	int b,w;
	do {b=rand()%MOD,w=Add(Mul(b,b),Mod(-a));}
		while (qpow(w,(MOD-1)>>1)!=MOD-1);
	Complex ans=qpow(Complex(b,1,w),(MOD+1)>>1);
	return min(ans.x,MOD-ans.x);
}

namespace poly
{
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
					a[j]=Add(x,y),a[j+mid]=Add(x,Mod(-y));
				}
		}
		if (type==1)
			return ;
		int inv=qpow(n,MOD-2);
		for (int i=0;i<n;i++)
			a[i]=Mul(a[i],inv);
		return ;
	}
	void inverse(int n,int *a,int *b,int *t)
	{
		if (n==1)
			return b[0]=qpow(a[0],MOD-2),void();
		int h=(n+1)>>1,len=1;
		while (len<(n<<1))
			len<<=1;
		inverse(h,a,b,t);
		fill(b+h,b+len,0);
		copy(a,a+n,t);
		fill(t+n,t+len,0);
		ntt(len,t,1);
		ntt(len,b,1);
		for (int i=0;i<len;i++)
			b[i]=Add(Mul(2,b[i]),Mod(-Mul(Mul(b[i],b[i]),t[i])));
		ntt(len,b,-1);
		return ;
	}
	void sqrt(int n,int *a,int *b,int *t1,int *t2)
	{
		if (n==1)
			return b[0]=modsqrt(a[0]),void();
		int h=(n+1)>>1;
		int len=1;
		while (len<2*n)
			len<<=1;
		sqrt(h,a,b,t1,t2);
		fill(b+h,b+len,0);
		fill(t1,t1+len,0);
		inverse(n,b,t1,t2);
		fill(t1+n,t1+len,0);
		copy(a,a+n,t2);
		fill(t2+n,t2+len,0);
		ntt(len,t2,1);
		ntt(len,t1,1);
		ntt(len,b,1);
		int inv2=qpow(2,MOD-2);
		for (int i=0;i<len;i++)
			b[i]=Mul(Add(Mul(b[i],b[i]),t2[i]),Mul(inv2,t1[i]));
		ntt(len,b,-1);
		return ;
	}
	void integral(int n,int *a,int *b)
	{
		for (int i=n-1;i;i--)
			b[i]=Mul(qpow(i,MOD-2),a[i-1]);
		b[0]=0;
		return ;
	}
	void derivation(int n,int *a,int *b)
	{
		for (int i=0;i<n-1;i++)
			b[i]=Mul(i+1,a[i+1]);
		b[n-1]=0;
		return ;
	}
	void ln(int n,int *a,int *b,int *t)
	{
		assert(a[0]==1);
		inverse(n,a,b,t);
		derivation(n,a,t);
		int len=1;
		while (len<(n<<1))
			len<<=1;
		fill(b+n,b+len,0);
		fill(t+n,t+len,0);
		ntt(len,b,1);
		ntt(len,t,1);
		for (int i=0;i<len;i++)
			t[i]=Mul(b[i],t[i]);
		ntt(len,t,-1);
		integral(n,t,b);
		return ;
	}
	void exp(int n,int *a,int *b,int *t1,int *t2)
	{
		if (n==1)
		{
			assert(a[0]==0);
			b[0]=1;
			return ;
		}
		int h=(n+1)>>1,len=1;
		while (len<(n<<1))
			len<<=1;
		exp(h,a,b,t1,t2);
		fill(b+h,b+len,0);
		ln(n,b,t1,t2);
		fill(t1+n,t1+len,0);
		copy(a,a+n,t2);
		fill(t2+n,t2+len,0);
		ntt(len,t2,1);
		ntt(len,t1,1);
		ntt(len,b,1);
		for (int i=0;i<len;i++)
			b[i]=Mul(b[i],Add(Add(1,t2[i]),Mod(-t1[i])));
		ntt(len,b,-1);
		return ;
	}
	void qpow(int n,int *a,int *b,int *t1,int *t2,int *t3,int k)
	{
		int len=1;
		while (len<(n<<1))
			len<<=1;
		ln(n,a,t3,t1);
		fill(t1,t1+len,0);
		for (int i=0;i<n;i++)
			t3[i]=Mul(t3[i],k);
		exp(n,t3,b,t1,t2);
		return ;
	}
}

const int MAXM = 400009;

int n,m;
int A[MAXM],C[MAXM],t1[MAXM],t2[MAXM];

int main()
{
//	freopen("CF438E.in","r",stdin);
//	freopen("CF438E.out","w",stdout);
	srand(19260817);
	int v;
	IO.scan(n,m);
	for (int i=0;i<n;i++)
	{
		IO.scan(v);
		if (v>m)
			continue;
		C[v]=Mod(-4);
	}
	m++;
	C[0]=1;
	poly::init();
	poly::sqrt(m,C,A,t1,t2);
	A[0]++;
	memset(t1,0,sizeof t1);
	poly::inverse(m,A,C,t1);
	for (int i=1;i<m;i++)
		IO.print(Mul(2,C[i]),'\n');
	IO.println();
	return 0;
}