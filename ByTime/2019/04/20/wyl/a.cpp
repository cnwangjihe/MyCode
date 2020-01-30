// Date      : 2019-04-20 09:21:45
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

const int MAXN = 400009;

struct SegmentTree
{
	int t[MAXN*4],All[MAXN*4];
	bool Xor[MAXN*4];
	void clear(){memset(All,-1,sizeof All);memset(Xor,0,sizeof Xor);}
	SegmentTree(){clear();}
	inline void Up(int u){t[u]=t[u<<1]+t[u<<1|1];}
	inline void Down(int u,int l,int r)
	{
		int mid=(l+r)>>1;
		if (~All[u])
		{
			t[u<<1]=All[u]*(mid-l+1);
			All[u<<1]=All[u];
			Xor[u<<1]=0;
			t[u<<1|1]=All[u]*(r-mid);
			All[u<<1|1]=All[u];
			Xor[u<<1|1]=0;
			All[u]=-1;
		}
		else if (Xor[u])
		{
			t[u<<1]=(mid-l+1)-t[u<<1];
			if (~All[u<<1])
				All[u<<1]^=1;
			else
				Xor[u<<1]^=1;
			t[u<<1|1]=(r-mid)-t[u<<1|1];
			if (~All[u<<1|1])
				All[u<<1|1]^=1;
			else
				Xor[u<<1|1]^=1;
			Xor[u]=0;
		}
		return ;
	}
	void Modify0(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
		{
			t[u]=0;
			All[u]=0,Xor[u]=0;
			return ;
		}
		Down(u,l,r);
		int mid=(l+r)>>1;
		if (al<=mid)
			Modify0(u<<1,l,mid,al,ar);
		if (ar>mid)
			Modify0(u<<1|1,mid+1,r,al,ar);
		Up(u);
		return ;
	}
	void Modify1(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
		{
			t[u]=r-l+1;
			All[u]=1,Xor[u]=0;
			return ;
		}
		Down(u,l,r);
		int mid=(l+r)>>1;
		if (al<=mid)
			Modify1(u<<1,l,mid,al,ar);
		if (ar>mid)
			Modify1(u<<1|1,mid+1,r,al,ar);
		Up(u);
		return ;
	}
	void Modify2(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
		{
			t[u]=r-l+1-t[u];
			if (~All[u])
				All[u]^=1;
			else
				Xor[u]^=1;
			return ;
		}
		Down(u,l,r);
		int mid=(l+r)>>1;
		if (al<=mid)
			Modify2(u<<1,l,mid,al,ar);
		if (ar>mid)
			Modify2(u<<1|1,mid+1,r,al,ar);
		Up(u);
		return ;
	}
	int Query(int u,int l,int r)
	{
		if (l==r)
			return l;
		Down(u,l,r);
		int mid=(l+r)>>1;
		if (t[u<<1]!=(mid-l+1))
			return Query(u<<1,l,mid);
		return Query(u<<1|1,mid+1,r);
	}
}ST;

int p[MAXN],t[MAXN];
long long v[MAXN],val[MAXN];
int n,q;

inline bool _cmp(int a,int b){return v[a]<v[b];}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	IO.scan(q);
	for (int i=1;i<=q;i++)
		IO.scan(t[i],v[i],v[i+q]);
	for (int i=1;i<=2*q;i++)
		p[i]=i;
	sort(p+1,p+(2*q)+1,_cmp);
	for (int i=1;i<=2*q;i++)
	{
		n++;
		if (v[p[i]]>val[v[p[i-1]]]+1)
			val[n++]=val[v[p[i-1]]]+1;
		while (i+1<=2*q && v[p[i]]==v[p[i+1]])
			v[p[i++]]=n;
		val[n]=v[p[i]];
		v[p[i]]=n;
	}
//	for (int i=1;i<=2*q;i++)
//		n=max(n,v[i]);
//	for (int i=1;i<=n;i++)
//		val[i]=i;
	for (int i=1;i<=q;i++)
	{
		if (t[i]==1)
			ST.Modify1(1,1,n,v[i],v[i+q]);
		else if (t[i]==2)
			ST.Modify0(1,1,n,v[i],v[i+q]);
		else if (t[i]==3)
			ST.Modify2(1,1,n,v[i],v[i+q]);
		if (ST.t[1]==n)
			IO.print(val[n]+1,'\n');
		else
			IO.print(val[ST.Query(1,1,n)],'\n');
	}
	return 0;
}