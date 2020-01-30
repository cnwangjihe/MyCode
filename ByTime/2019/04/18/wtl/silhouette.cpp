// Date      : 2019-04-18 10:39:41
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
		  MOD  = 1000000007;

int a[MAXN],b[MAXN];
int v[1009][1009];
int ans=0,n;

void Search(int k)
{
	if (k==n*n)
	{
		int t;
		for (int i=0;i<n;i++)
		{
			t=0;
			for (int j=0;j<n;j++)
				t=max(t,v[i][j]);
			if (t!=b[i])
				return ;
		}
		for (int i=0;i<n;i++)
		{
			t=0;
			for (int j=0;j<n;j++)
				t=max(t,v[j][i]);
			if (t!=a[i])
				return ;
		}
		ans=(ans+1)%MOD;
		return ;
	}
	int x=k/n,y=k%n;
	for (int i=0;i<=min(a[y],b[x]);i++)
	{
		v[x][y]=i;
		Search(k+1);
		v[x][y]=0;
	}
	return ;
}

int main()
{
//	freopen("silhouette.in","r",stdin);
//	freopen("silhouette.out","w",stdout);
	IO.scan(n);
	for (int i=0;i<n;i++)
		IO.scan(a[i]);
	for (int i=0;i<n;i++)
		IO.scan(b[i]);
	sort(a,a+n);
	sort(b,b+n);
	Search(0);;
	IO.print(ans,'\n');
	return 0;
}