#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100000 + 10;
const long long MOD = 998244353ll;

long long n,k,cnt[32];
long long ans;
long long p[MAXN],g[MAXN];

void gcd(long long a,long long b,long long &d,long long &x,long long &y)
{
	if(b) gcd(b,a%b,d,y,x),y-=1ll*a/b*x;
	else {d=a;x=1;y=0;}
}
long long exGcd(long long a)
{
	long long d,x,y;
	gcd(a,MOD,d,x,y);
	return (x+MOD)%MOD;
}

long long CNK(long long i,long long j)
{
	if(i>j) return 0ll;
	if(i==0ll || i==j) return 1ll;
	return g[j-i]*(p[j]*g[i]%MOD)%MOD;
}

int main()
{
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	p[1]=1; g[1]=1;
	for (int i=2;i<MAXN;i++)
	{
		p[i]=p[i-1]*i;
		p[i]%=MOD;
		g[i]=exGcd(p[i]);
	}
	long long x;
	scanf("%lld%lld",&n,&k);
	for (int i=0;i<n;i++)
	{
		scanf("%lld",&x);
		int j=0;
		while (x>0)
		{
			cnt[j]+=x&1;
			j++;
			x>>=1;
		}
	}
	
	for (int i=0;i<31;i++)
	{
		for (int j=1;j<=k;j+=2)
		{
			ans+=(1ll*CNK(j,cnt[i])*CNK(k-j,n-cnt[i])%MOD)*(1<<i)%MOD;
			ans%=MOD;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
