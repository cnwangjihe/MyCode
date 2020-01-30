// Date      : 2019-04-20 09:32:32
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

const int MAXN = 2509,
		  MOD  = 1000000007;

int n,m;

struct BinaryIndexTree
{
	int v[MAXN];
	void clear(){memset(v,0,sizeof v);}
	BinaryIndexTree(){clear();}
	inline void Add(int x,int a){for (;x<=m;x+=x&-x) v[x]+=a;}
	int Ask(int x)
	{
		int sum=0;
		for (;x;x-=x&-x)
			sum+=v[x];
		return sum;
	}
};

BinaryIndexTree T,S;
bool vis[MAXN];
int p[MAXN][MAXN];
int c[MAXN];
int ans=0;

inline Mul(const int &a,const int &b){return 1ll*a*b%MOD;}
inline Add(const int &a,const int &b){return a+b>=MOD?a+b-MOD:a+b;}
inline Mod(const int &a){return a<0?a+MOD:a;}

void Update(int x)
{
	if (vis[x])
		return ;
	vis[x]=1;
	T.Add(x,1);
	S.Add(x,x);
	return ;
}

int main()
{
//	freopen("rectangle.in","r",stdin);
//	freopen("rectangle.out","w",stdout);
	int x,y;
	IO.scan(n);
	for (int i=0;i<n;i++)
		IO.scan(x,y),p[x][c[x]++]=y,m=max(m,x);
	for (int i=1;i<=m;i++)
	{
		sort(p[i],p[i]+c[i]);
		p[i][c[i]]=m+1;
	
	}
	int Max,tMax,pos,pi,pj,t1,t2;
	for (int i=1;i<=m;i++)
	{
		if (!c[i])
			continue;
		T.clear(),S.clear();
		memset(vis,0,sizeof vis);
		for (int j=0;j<c[i];j++)
			Update(p[i][j]);
		for (int j=i-1;j;j--)
		{
			if (!c[j])
				continue;
			pi=0,pj=0,Max=max(p[i][0],p[j][0]);
			for (int k=0;k<c[j];k++)
				Update(p[j][k]);
			while (p[i][pi+1]<=Max)
				pi++;
			while (p[j][pj+1]<=Max)
				pj++;
			while (pi<c[i] && pj<c[j])
			{
				tMax=min(p[i][pi+1],p[j][pj+1]);
				pos=min(p[i][pi],p[j][pj]);
				t1=S.Ask(tMax-1)-S.Ask(Max-1);
				t2=T.Ask(tMax-1)-T.Ask(Max-1);
				ans=Add( ans, Mul( Add( Mul(t1,T.Ask(pos)) , Mod(-Mul(t2,S.Ask(pos))) ) , i-j ) );
				Max=tMax;
				if (p[i][pi+1]<=Max)
					pi++;
				if (p[j][pj+1]<=Max)
					pj++;
			}
		}
	}
	IO.print(ans,'\n');
	return 0;
}
