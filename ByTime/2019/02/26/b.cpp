// Date      : 2019-02-26 10:22:23
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None
#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4000009,
		  DINF = MAXN*2;
const long long LLDINF = 1000000000000000009ll;

long long f[MAXN][2],a[MAXN],b[MAXN];
int l[MAXN][2],r[MAXN][2];
long long Max=0;
int n,k;

inline char nextchar()
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline long long read()
{
	static long long x;
	x = 0;
	static char ch = 0;
	while (!isdigit(ch)) { ch = nextchar(); }
	while (isdigit(ch)) { x = x * 10 + (ch ^ 48); ch = nextchar(); }
	return x;
}

pair<long long,pair<int,int> > check(const long long& v)
{
	for (int i=1;i<=n;i++)
		b[i]=a[i]-v;
	f[0][0]=0,f[0][1]=-LLDINF;
	l[0][0]=0,l[0][1]=DINF;
	r[0][0]=0,r[0][1]=DINF;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=f[i-1][0];
		l[i][0]=l[i-1][0];
		r[i][0]=r[i-1][0];
		f[i][1]=f[i-1][1];
		l[i][1]=l[i-1][1];
		r[i][1]=r[i-1][1];
		if (f[i-1][0]-a[i]>f[i][1])
		{
			f[i][1]=f[i-1][0]-a[i];
			l[i][1]=l[i-1][0]+1;
			r[i][1]=r[i-1][0]+1;
		}
		else if (f[i-1][0]-a[i]==f[i][1])
		{
			l[i][1]=min(l[i][1],l[i-1][0]+1);
			r[i][1]=max(r[i][1],r[i-1][0]+1);
		}
		if (f[i-1][1]+b[i]>f[i][0])
		{
			f[i][0]=f[i-1][1]+b[i];
			l[i][0]=l[i-1][1]+1;
			r[i][0]=r[i-1][1]+1;
		}
		else if (f[i-1][1]+b[i]==f[i][0])
		{
			l[i][0]=min(l[i][0],l[i-1][1]+1);
			r[i][0]=min(r[i][0],r[i-1][1]+1);
		}
	}
	if (f[n][1]>f[n][0])
		f[n][0]=f[n][1],l[n][0]=l[n][1],r[n][0]=r[n][1];
	else if (f[n][1]==f[n][0])
		l[n][0]=min(l[n][0],l[n][1]),r[n][0]=min(r[n][0],r[n][1]);
	return make_pair(f[n][0],make_pair(l[n][0]/2,r[n][0]/2));
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		a[i]=read(),Max=max(Max,a[i]);
	long long l=0,r=Max+3,mid;
	long long ans=0;
	pair<long long,pair<int,int> > tmp;
	tmp=check(0);
	if (tmp.second.first<=k)
		return printf("%lld\n",tmp.first),0;
	while (l+1<r)
	{
		mid=(l+r)/2;
		tmp=check(mid);
		if (tmp.second.first>k)
			l=mid;
		else
		{
			r=mid;
			ans=(tmp.first+min(tmp.second.second,k)*mid);
		}
	}
	printf("%lld\n",ans);
	return 0;
}