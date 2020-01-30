// Date      : 2019-04-25 07:39:09
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

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
		  MAXK = 21,
		  INF  = 1000000009;

int sa[MAXN],rank[MAXN],tmp[MAXN],h[MAXN],cnt[MAXN];
int t[MAXN*2],f[MAXN*2];
int Min[MAXN][MAXK];
std::pair<int,int> st[MAXN*2];
char s[MAXN];
int n,m;
long long ans=0;

inline bool _cmp(int *a,int i,int j,int len){return a[i]==a[j] && a[i+len]==a[j+len];}

void GetSA(int n,int m,int *rank,int *sa,int *tmp)
{
	for (int i=0;i<m;i++) cnt[i]=0;
	for (int i=0;i<n;i++) cnt[rank[i]]++;
	for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for (int i=n-1;~i;i--) sa[--cnt[rank[i]]]=i;
	for (int j=1,p=1;m^n;j<<=1,m=p)
	{
		p=0;
		for (int i=n-j;i<n;i++) tmp[p++]=i;
		for (int i=0;i<n;i++) if (sa[i]>=j) tmp[p++]=sa[i]-j;
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[tmp[i]]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;~i;i--) sa[--cnt[rank[tmp[i]]]]=tmp[i];
		for (int i=0;i<n;i++) std::swap(tmp[i],rank[i]);
		rank[sa[0]]=0,p=1;
		for (int i=1;i<n;i++)
			rank[sa[i]]=_cmp(tmp,sa[i],sa[i-1],j)?p-1:p++;
	}
	return ;
}

template<typename T>
void GetHeight(int n,int *rank,int *sa,T *s,int *h)
{
	int x=0,j;
	for (int i=0;i<n;i++)
	{
		x-=(x!=0);
		if (!rank[i])
			continue;
		j=sa[rank[i]-1];
		while (s[i+x]==s[j+x])
			x++;
		h[rank[i]]=x;
	}
	return ;
}

void RMQ()
{
	for (int i=0;i<n;i++)
		Min[i][0]=h[i];
	int m=LOG2(n);
	for (int j=1;j<=m;j++)
		for (int i=0;i+(1<<j)-1<n;i++)
			Min[i][j]=std::min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
	return ;
}

inline int QueryMin(int l,int r)
{
	if (l>r)
		return INF;
	int len=LOG2(r-l+1);
	return std::min(Min[l][len],Min[r-(1<<len)+1][len]);
}

int main()
{
//	freopen("P3649.in","r",stdin);
//	freopen("P3649.out","w",stdout);
	int cnt=0;
	memset(s,-1,sizeof s);
	memset(tmp,-1,sizeof tmp);
	IO.scan(s);
	n=strlen(s);
	s[n]=-1;
	for (int i=0;i<n;i++)
		s[i]-='a';
	for (int i=0;i<n;i++)
		rank[i]=s[i];
	GetSA(n,26,rank,sa,tmp);
	GetHeight(n,rank,sa,s,h);
//	for (int i=0;i<n;i++)
//		std::cerr << i << ' ' << rank[i] << ' ' << sa[i] << ' ' << h[i] << '\n';
	RMQ();
	m=0;
	t[m++]=27;
	for (int i=0;i<n;i++)
		t[m++]=26,t[m++]=s[i];
	t[m++]=26,t[m++]=28;
	f[0]=0,f[1]=0,f[2]=1;
	int p=2;
	for (int i=3;i<m;i++)
	{
		f[i]=std::max(0,std::min(f[2*p-i],p+f[p]-i));
		while (t[i-f[i]-1]==t[i+f[i]+1])
		{
			f[i]++;
			if ((i-f[i])&1)
				st[cnt++]=std::make_pair((i-f[i])>>1,f[i]);
		}
		if (p+f[p]<i+f[i])
			p=i;
	}
	for (int i=0;i<cnt;i++)
	{
		p=rank[st[i].first];
		int l=1,r=p+1,mid,sum=0;
		while (l+1<r)
		{
			mid=(l+r)>>1;
			if (QueryMin(p-mid+2,p)>=st[i].second)
				l=mid;
			else
				r=mid;
		}
		sum+=l;
		l=1,r=n-p;
		while (l+1<r)
		{
			mid=(l+r)>>1;
			if (QueryMin(p+1,p+mid-1)>=st[i].second)
				l=mid;
			else
				r=mid;
		}
		sum+=l-1;
		ans=std::max(ans,1ll*sum*st[i].second);
	}
	IO.print(ans,'\n');
	return 0;
}