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
const long long LLINF = 1000000000000000009ll;

long long f[MAXN][2],a[MAXN],b[MAXN];
int g[MAXN][2];
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

pair<long long,int> check(const long long& v)
{
	for (int i=1;i<=n;i++)
		b[i]=a[i]-v;
	f[0][0]=0,f[0][1]=-LLINF;
	g[0][0]=0,g[0][1]=DINF;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=f[i-1][0];
		g[i][0]=g[i-1][0];
		f[i][1]=f[i-1][1];
		g[i][1]=g[i-1][1];
		if (f[i-1][0]-a[i]>f[i][1] || (f[i-1][0]+a[i]==f[i][1] && g[i-1][0]+1<g[i][1]))
		{
			f[i][1]=f[i-1][0]-a[i];
			g[i][1]=g[i-1][0]+1;
		}
		if (f[i-1][1]+b[i]>f[i][0] || (f[i-1][1]+b[i]==f[i][0] && g[i-1][1]+1<g[i][0]))
		{
			f[i][0]=f[i-1][1]+b[i];
			g[i][0]=g[i-1][1]+1;
		}
	}
	return make_pair(f[n][0],g[n][0]/2);
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		a[i]=read(),Max=max(Max,a[i]);
	long long l=0,r=Max+2,mid,ans=0;
	pair<long long,int> tmp;
	while (l+1<r)
	{
		mid=(l+r)/2ll;
		tmp=check(mid);
		if (tmp.second>k)
			l=mid;
		else
		{
			r=mid;
			ans=tmp.first+tmp.second*mid;
		}
	}
	printf("%lld\n",ans);
	return 0;
}