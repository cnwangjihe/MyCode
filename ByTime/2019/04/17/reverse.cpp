// Date      : 2019-04-17 10:42:19
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
		  INF  = 1000000009;

int a[MAXN],disl[MAXN],disr[MAXN];
bool visl[MAXN],visr[MAXN],vis[MAXN];
int n,m,k,s;
queue<int> Q;
stack<int> S;

void Solve2()
{
	a[s]=0;
	Q.push(s);
	bool f=(k&1);
	int lim=(k>>1),u,t,lp,rp,p;
	while (!Q.empty())
	{
		u=Q.front(),Q.pop();
		lp=u-lim+1,rp=u+f+lim;
	//	cerr << lp << ' ' << rp << '\n';
		p=-1;
		for (int v=u+1+f;v<=n && v<u+k && rp<=n;v+=2)
		{
			p=v;
			if (lp<1 || a[v]==-1)
				continue;
			if (a[v]<=a[u]+1 && visr[v] && v<disr[v]-2)
			{
				t=(disr[v]-v-2)>>1;
				lp+=t,rp+=t;
				v=disr[v]-2;
				continue;
			}
			if (a[v]>a[u]+1)
			{
				a[v]=a[u]+1;
				disr[v]=u+k,visr[v]=1;
				S.push(v),Q.push(v);
			}
			lp++,rp++;
		}
		while (~p && !S.empty())
		{
			t=S.top();
			disr[t]=p,visr[t]=1;
			S.pop();
		}
		p=-1;
		lp=u-f-lim,rp=u+lim-1;
		for (int v=u-f-1;v>0 && v>u-k && lp>0;v-=2)
		{
			p=v;
			if (rp>n || a[v]==-1)
				continue;
			if (a[v]<=a[u]+1 && visl[v] && v>disl[v]+2)
			{
				t=(v-disl[v]-2)>>1;
				lp-=t,rp-=t;
				v=disl[v]+2;
				continue;
			}
			if (a[v]>a[u]+1)
			{
				a[v]=a[u]+1;
				disl[v]=u-k+1,visl[v]=1;
				S.push(v),Q.push(v);
			}
			lp--,rp--;
		}
		while (~p && !S.empty())
		{
			t=S.top();
			disl[t]=p,visl[t]=1;
			S.pop();
		}
	}
}

void Solve1()
{
	vis[s]=1;
	a[s]=0;
	Q.push(s);
	int u,t;
	while (!Q.empty())
	{
		u=Q.front(),Q.pop();
		for (int i=(k&1)+1;i<=k;i+=2)
		{
			if (u-i<=0)
				break;
			if (vis[u-i] || a[u-i]==-1)
				continue;
			t=(k-(i+1))>>1;
			if (u-i-t>0 && u+t<=n)
			{
				a[u-i]=a[u]+1;
				vis[u-i]=1;
				Q.push(u-i);
			}
		}
		for (int i=(k&1)+1;i<=k;i+=2)
		{
			if (u+i>n)
				break;
			if (vis[u+i] || a[u+i]==-1)
				continue;
			t=(k-(i+1))>>1;
			if (u-t>0 && u+i+t<=n)
			{
				a[u+i]=a[u]+1;
				vis[u+i]=1;
				Q.push(u+i);
			}
		}
	}
	return ;
}

int main()
{
//	int t=clock();
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int v;
	IO.scan(n,k,m,s);
	memset(visl,0,sizeof visl);
	memset(visr,0,sizeof visr);
	fill(a+1,a+n+1,INF);
	for (int i=0;i<m;i++)
		IO.scan(v),a[v]=-1;
	if (n<=1000)
		Solve1();
	else
		Solve2();
	for (int i=1;i<=n;i++)
		IO.print(a[i]==INF?-1:a[i],' ');
	IO.println();
//	cerr << clock()-t << endl;
	return 0;
}