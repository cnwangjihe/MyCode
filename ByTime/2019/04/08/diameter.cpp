// Date      : 2019-04-08 10:41:53
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

int k;

int main()
{
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);
	IO.scan(k);
	int n=4998;
	for (int a=1;a<=n;a++)
		for (int b=0;a+b<=n;b++)
		{
			if ((k-a*b)%(a+b))
				continue;
			int c=(k-a*b)/(a+b);
			int cnt=a+b+c+(!!a)+(!!b)+(!!c);
			if (cnt+1>5000 || (c==0 && b==0))
				continue;
			cerr << a << ' ' << b << ' ' << c << ' ' << cnt << '\n';
			int fp=1,u;
			IO.print(cnt+1,"\n");
			if (a)
			{
				u=++fp;
				IO.print(u,' ',1," 1\n");
				for (int i=0;i<a;i++)
					IO.print(++fp,' ',u," 1\n");
			}
			if (b)
			{
				u=++fp;
				IO.print(u,' ',1," 1\n");
				for (int i=0;i<b;i++)
					IO.print(++fp,' ',u," 1\n");
			}
			if (c)
			{
				u=++fp;
				IO.print(u,' ',1," 1\n");
				for (int i=0;i<c;i++)
					IO.print(++fp,' ',u," 1\n");
			}
			return 0;
		}
	return 0;
}