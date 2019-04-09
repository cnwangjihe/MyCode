// Date      : 2019-04-09 09:38:01
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

const int MAXM = 100009;

int m;
long long sum=0,ans=0,cntF=0,n;
long long x[MAXM];
int len[MAXM],Max[MAXM],p[MAXM];
char s[2*MAXM];

int main()
{
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
	memset(Max,-1,sizeof Max);
	IO.scan(n,m);
	for (int i=1;i<=m;i++)
	{
		IO.scan(s,x[i]);
		len[i]=strlen(s);
		for (int j=len[i]-1;~j;j--)
			p[i]+=(s[j]=='M'?1:-1),Max[i]=max(Max[i],p[i]-1);
		cntF+=-1ll*p[i]*x[i];
	}
	if (cntF<0)
		return IO.print(-1),0;
	for (int i=m;i;i--)
	{
		if (p[i]>0)
			ans=max(ans,sum+1ll*p[i]*(x[i]-1)+Max[i]);
		else
			ans=max(ans,sum+Max[i]);
		sum+=1ll*x[i]*p[i];
	}
	IO.print(ans,'\n');
	return 0;
}