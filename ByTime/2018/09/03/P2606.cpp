#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1000009;

ll f[MAXN],fav[MAXN],fac[MAXN];
int n,m,MOD;

ll qpow(ll a,int k)
{
	ll ans=1;
	for (int i=0;(1<<i)<=k;i++,a=a*a%MOD)
		if ((1<<i)&k)
			ans=ans*a%MOD;
	return ans;
}

ll Lucas(int a,int b)
{
	if (a<b)
		return 0;
	if (a<=m && b<=m)
		return fac[a]*fav[a-b]%MOD*fav[b]%MOD;
	return Lucas(a/MOD,b/MOD)*Lucas(a%MOD,b%MOD)%MOD;
}

int main()
{
	scanf("%d%d",&n,&MOD);
	m=min(n,MOD-1);
	fac[1]=1;
	for (int i=2;i<=m;i++)
		fac[i]=fac[i-1]*(ll)i%MOD;
	fav[m]=qpow(fac[m],MOD-2);
	fav[0]=1;
	for (int i=m-1;i;i--)
		fav[i]=fav[i+1]*(ll)(i+1)%MOD;
	f[1]=1,f[2]=1,f[3]=2;
	int j=4,mid=3,l=1,r=1;
	for (int i=4;i<=n;i++)
	{
		if (i==j)
			j*=2,mid*=2;
		if (i<mid)
			l++;
		else
			r++;
		f[i]=Lucas(i-1ll,l)*f[l]%MOD*f[r]%MOD;
	}
	printf("%lld\n",f[n]);
	return 0;
}