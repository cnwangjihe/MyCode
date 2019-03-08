#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mx=1e5+10;
const int mod=1e9+7;
int n,m,k;
int w[mx];
int ct[mx];
ll fac[10000007];

ll power(ll a,int k)
{
	if(!k) return 1;
	if(k==1) return a%mod;
	ll ret=power(a,k/2);
	ret=1ll*ret*ret%mod;
	if(k&1) ret=1ll*ret*a%mod;
	return ret;
}

ll C(int n,int k)
{
	if (k<0) return 1;
	if(k>n) return 0;
	return fac[n]*power(fac[k],mod-2)%mod*power(fac[n-k],mod-2)%mod;
}

int sum=0,Max=0;
void pre()
{	
	for(int i=1;i<=m;i++) ct[w[i]]++,sum+=w[i],Max=max(Max,w[i]);
	fac[0]=1;
	for(int i=1;i<=n+k;i++)
		fac[i]=(fac[i-1]*i)%mod;
}

ll f[mx],s[mx];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
		scanf("%d",&w[i]);
	
	pre();
	
	f[0]=1;
	for(int i=0;i<=sum;i++) s[i]=1;
	
	for(int i=1;i<=m;i++)
	{
		for(int j=sum;j>=0;j--)
			(f[j]=s[j]-(j-w[i]-1>=0?s[j-w[i]-1]:0))%=mod;
		s[0]=f[0];
		for(int j=1;j<=sum;j++)
			s[j]=(s[j-1]+f[j])%mod;
	}


	ll ans=0;
	for(int i=0;i<=sum;i++)
		(ans+=(1ll*f[i]*C(n-m+k-i-1,n-m-1)%mod))%=mod;
		
	printf("%lld\n",ans);
	
	return 0;
}
