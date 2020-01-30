// Date      : 2019-04-25 15:32:21
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

const int MAXN = 300009,
		  MAXC = 26,
		  MAXK = 20;

struct SAM
{
	int fp;
	queue<int> Q;
	int link[MAXN*2],len[MAXN*2],siz[MAXN*2];
	int cnt[MAXN*2],tmp[MAXN*2];
	int next[MAXN*2][MAXC];
	int jump[MAXN*2][MAXK];
	SAM(){fp=1;memset(next,-1,sizeof next);memset(link,-1,sizeof link);}
	void Extend(int c,int &last)
	{
		int u=fp++,p;
		len[u]=len[last]+1;
		siz[u]=1;
		for (p=last;~p && !~next[p][c];p=link[p])
			next[p][c]=u;
		last=u;
		if (!~p)
			return link[u]=0,void();
		int q=next[p][c];
		if (len[p]+1==len[q])
			return link[u]=q,void();
		int clone=fp++;
		copy(next[q],next[q]+MAXC,next[clone]);
		link[clone]=link[q];
		len[clone]=len[p]+1;
		link[q]=clone,link[u]=clone;
		for (;~p && next[p][c]==q;p=link[p])
			next[p][c]=clone;
		return ;
	}
	void BuildJump()
	{
		int n=0,u;
		for (int i=1;i<fp;i++)
			cnt[link[i]]++;
		for (int i=1;i<fp;i++)
			if (!cnt[i])
				Q.push(i);
		while (!Q.empty())
		{
			u=Q.front();Q.pop();
			if (!u)
				continue;
			siz[link[u]]+=siz[u];
			if (!--cnt[link[u]])
				Q.push(link[u]);
			tmp[n++]=u;
		}
		for (int i=n-1;~i;i--)
		{
			jump[tmp[i]][0]=link[tmp[i]];
			for (int j=0;jump[tmp[i]][j];j++)
				jump[tmp[i]][j+1]=jump[jump[tmp[i]][j]][j];
		}
		return ;
	}
	int GetSize(int u,int val)
	{
		for (int i=MAXK-1;~i;i--)
			if (len[jump[u][i]]>=val)
				u=jump[u][i];
		return siz[u];
	}
};

SAM SAM;
int t[MAXN*2],f[MAXN*2],pos[MAXN];
pair<int,int> st[MAXN*2];
char s[MAXN];
int n,m;
long long ans=0;

int main()
{
//	freopen("P3649_SAM.in","r",stdin);
//	freopen("P3649_SAM.out","w",stdout);
	int cnt=0;
	IO.scan(s);
	n=strlen(s);
	int last=0;
	for (int i=0;i<n;i++)
	{
		s[i]-='a';
		SAM.Extend(s[i],last);
		pos[i]=last;
	}
	SAM.BuildJump();
	m=0;
	t[m++]=27;
	for (int i=0;i<n;i++)
		t[m++]=26,t[m++]=s[i];
	t[m++]=26,t[m++]=28;
	f[0]=0,f[1]=0,f[2]=1;
	int p=2;
	for (int i=3;i<m;i++)
	{
		f[i]=max(0,min(f[2*p-i],p+f[p]-i));
		while (t[i-f[i]-1]==t[i+f[i]+1])
		{
			f[i]++;
			if ((i-f[i])&1)
				st[cnt++]=make_pair((i-f[i])>>1,f[i]);
		}
		if (p+f[p]<i+f[i])
			p=i;
	}
	for (int i=0;i<cnt;i++)
	{
		p=st[i].first+st[i].second-1;
		ans=max(ans,1ll*SAM.GetSize(pos[p],st[i].second)*st[i].second);
	}
	IO.print(ans,'\n');
	return 0;
}