// Date      : 2019-04-04 09:31:09
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
	inline void prints(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void prints(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline int scans(char *s,int (*check)(int c)=isalnum)
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
	inline int scans(string &s,int (*check)(int c)=isalnum)
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
		inline void print(Number x,Numbers... X) {print(x),putchar(' '),print(X...);}
		template<typename Number,typename... Numbers>
		inline int scan(Number &x,Numbers &... X) {return scan(x)+scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
}IO;

const int MAXN = 1050000,
		  MAXC = 4,
		  MOD  = 1000000007;

bool vis[MAXN*2];
int siz[MAXN*2];
int m[MAXN],root[MAXN],r[MAXN];
int nxt[MAXN][MAXC],ext[MAXN][MAXC];
string s[MAXN];
char ans[MAXN];
int n;

inline int Check(int c){return c=='A' || c=='C' || c=='G' || c=='T';}

inline int GetNum(char c)
{
	switch (c)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
	}
	return -1;
}

inline char GetChar(int id)
{
	switch (id)
	{
		case 0: return 'A'; break;
		case 1: return 'C'; break;
		case 2: return 'G'; break;
		case 3: return 'T'; break;
	}
	return -1;
}

struct SAM
{
	int link[MAXN*2],len[MAXN*2];
	int next[MAXN*2][MAXC];
	bool end[MAXN*2];
	int fp;
	SAM()
	{
		fp=0;
		memset(next,-1,sizeof next);
		memset(link,-1,sizeof link);
		memset(end,0,sizeof end);
		memset(len,0,sizeof len);
	}
	void Copy(int a,int b)
	{
		for (int i=0;i<MAXC;i++)
			next[a][i]=next[b][i];
		link[a]=link[b];
		end[a]=end[b];
	}
	int New(){return fp++;}
	void Insert(int &last,int c,int i)
	{
		int p,q,clone;
		int cur=New();
		len[cur]=len[last]+1;
		for (p=last;p!=-1 && next[p][c]==-1;p=link[p])
			next[p][c]=cur;
		if (p==-1)
		{
			link[cur]=root[i];
			last=cur;
			return ;
		}
		q=next[p][c];
		if (len[p]+1==len[q])
		{
			link[cur]=q;
			last=cur;
			return ;
		}
		clone=New();
		Copy(clone,q);
		len[clone]=len[p]+1;
		link[cur]=clone;
		link[q]=clone;
		for (;(~p) && next[p][c]==q;p=link[p])
			next[p][c]=clone;
		last=cur;
		return ;
	}
	int Solve0(int u)
	{
		if (vis[u])
			return siz[u];
		vis[u]=1,siz[u]=1;
		for (int i=0;i<4;i++)
			if (~next[u][i])
				(siz[u]+=Solve0(next[u][i]))%=MOD;
		return siz[u];
	}
	int Solve1(int u,int m,char *s)
	{
		IO.prints(s);
		IO.println();
		int ans=1;
		for (int i=0;i<4;i++)
		{
			if (!~next[u][i])
				continue;
			s[m]=GetChar(i);
			(ans+=Solve1(next[u][i],m+1,s))%=MOD;
		}
		s[m-1]='\0';
		return ans;
	}
}SAM;

int main()
{
	freopen("copy.in","r",stdin);
	freopen("copy.out","w",stdout);
	memset(nxt,-1,sizeof nxt);
	int t;
	IO.scan(n);
	for (int i=0;i<n;i++)
	{
		m[i]=IO.scans(s[i],Check);
		for (int j=0;j<m[i];j++)
			s[i][j]=GetNum(s[i][j]),ext[i][(int)s[i][j]]=1;
	}
	IO.scan(t);
	for (int i=n-1;i;i--)
		for (int j=0;j<4;j++)
			nxt[i-1][j]=(ext[i][j]?i:nxt[i][j]);
	int lst;
	for (int i=0;i<n;i++)
	{
		root[i]=SAM.New();
	//	cerr << root[i] << endl;
		lst=root[i];
		for (int j=0;j<m[i];j++)
			SAM.Insert(lst,s[i][j],i);
	}
	for (int i=n-2;~i;i--)
		for (int j=root[i];j!=root[i+1];j++)
			for (int k=0;k<4;k++)
				if (!~SAM.next[j][k])
					SAM.next[j][k]=SAM.next[root[i+1]][k];
	if (t==0)
		IO.print(SAM.Solve0(root[0]));
	else
		IO.print(SAM.Solve1(root[0],0,ans));
	return 0;
}