// Date      : 2019-01-04 23:18:37
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1097/problem/D
// Algorithm : DP
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXK = 100009;
const long long MOD = 1000000007ll;

long long p[MAXK],cnt[MAXK];
long long ans=1;
long long fac[MAXK],fav[MAXK],inv[MAXK],f[MAXK],g[MAXK];
int fp=0;
long long n,k;

long long qpow(long long a,long long k)
{
	long long ans=1ll;
	for (long long i=0;(1ll<<i)<=k;i++,a=a*a%MOD)
		if ((1ll<<i)&k)
			ans=ans*a%MOD;
	return ans;
}

void init()
{
	// fac[0]=fav[0]=1;
	// for (int i=1;i<MAXK;i++)
	// 	fac[i]=fac[i-1]*i%MOD;
	// fav[MAXK-1]=qpow(fac[MAXK-1],MOD-2);
	// for (int i=MAXK-2;i;i--)
	// 	fav[i]=fav[i+1]*(i+1)%MOD;
	inv[1]=1;
	for (int i=2;i<MAXK;i++)
		inv[i]=qpow(i,MOD-2);
	return ;
}

long long calc(long long p,long long c)
{
	long long ans=0,sum;
	
	for (int i=0;i<=c;i++)
		f[i]=0,g[i]=0;
	f[c]=1;
	for (int j=0;j<k;j++)
	{
		for (int i=0;i<=c;i++)
			for (int o=0;o<=i;o++)
				(g[o]+=f[i]*inv[i+1]%MOD)%=MOD;
		for (int i=0;i<=c;i++)
			f[i]=g[i],g[i]=0;
	}
	sum=1;
	for (int i=0;i<=c;i++)
	{
		(ans+=sum*f[i]%MOD)%=MOD;
		(sum*=p)%=MOD;
	}
	return ans;
}

int main()
{
//	freopen("CF1097D.in","r",stdin);
//	freopen("CF1097D.out","w",stdout);
	init();
	scanf("%lld%lld",&n,&k);
	long long c;
	for (long long i=2;i*i<=n;i++)
	{
		if (n%i)
			continue;
		c=0;
		while (!(n%i))
			n/=i,c++;
		p[fp]=i;
		cnt[fp++]=c;
	}
	if (n!=1)
	{
		p[fp]=n;
		cnt[fp++]=1;
	}
	for (int i=0;i<fp;i++)
		ans=ans*calc(p[i],cnt[i])%MOD;
	printf("%lld\n",ans);
	return 0;
}