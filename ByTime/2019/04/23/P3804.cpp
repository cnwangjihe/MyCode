// Date      : 2019-04-23 15:22:08
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

const int MAXN = 1000009,
		  MAXC = 26;

queue<int> Q;

struct SAM
{
	int link[MAXN*2],len[MAXN*2],siz[MAXN*2];
	int nxt[MAXN*2][MAXC];
	int cnt[MAXN*2];
	int fp;
	SAM()
	{
		fp=1;
		memset(link,-1,sizeof link);
		memset(nxt,-1,sizeof nxt);
		memset(siz,0,sizeof siz);
	}
	void Extend(int c,int &last)
	{
		int u=fp++,p;
		len[u]=len[last]+1;
		siz[u]=1;
		for (p=last;~p && !~nxt[p][c];p=link[p])
			nxt[p][c]=u;
		if (!~p)
		{
			link[u]=0;
			last=u;
			return ;
		}
		int q=nxt[p][c];
		if (len[p]+1==len[q])
		{
			link[u]=q;
			last=u;
			return ;
		}
		int clone=fp++;
		copy(nxt[q]+0,nxt[q]+MAXC,nxt[clone]);
		link[clone]=link[q];
		len[clone]=len[p]+1;
		link[u]=clone,link[q]=clone;
		for (;~p && nxt[p][c]==q;p=link[p])
			nxt[p][c]=clone;
		last=u;
		return ;
	}
	long long Calc()
	{
		memset(cnt,0,sizeof cnt);
		while (!Q.empty())
			Q.pop();
		for (int i=1;i<fp;i++)
			cnt[link[i]]++;
		for (int i=1;i<fp;i++)
			if (!cnt[i])
				Q.push(i);
		long long ans=0;
		while (!Q.empty())
		{
			int u=Q.front();Q.pop();
			if (siz[u]!=1)
				ans=max(ans,1ll*len[u]*siz[u]);
			siz[link[u]]+=siz[u];
			if (!--cnt[link[u]])
				Q.push(link[u]);
		}
		return ans;
	}
};

SAM SAM;

char s[MAXN];
int n;

int main()
{
	freopen("SAM.in","r",stdin);
//	freopen("SAM.out","w",stdout);
	IO.scan(s);
	n=strlen(s);
	int last=0;
	for (int i=0;i<n;i++)
		SAM.Extend(s[i]-'a',last);
	IO.print(SAM.Calc(),'\n');
	return 0;
}