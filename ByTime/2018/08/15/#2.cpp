#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2005;
const int mod=998244353;
LL l1,l2,p1,p2,dp1,dp2,ans,cp;
LL f[N][N];

LL qpow(LL x,int y)
{
	LL ret=1;
	for(;y;y>>=1,x=(LL)x*x%mod) if(y&1) ret=(LL)ret*x%mod;
	return ret;
}

int main()
{
	
	scanf("%lld%lld%lld%lld",&l1,&l2,&p1,&p2);p1=qpow(p1,mod-2);p2=qpow(p2,mod-2);
	dp1=(1-p1+mod)%mod;dp2=(1-p2+mod)%mod;cp=(1-dp1*dp2%mod+mod)%mod;cp=qpow(cp,mod-2);
	f[0][0]=1;
	cerr << cp << endl; 
	for(int i=0;i<=l1;++i)
		for(int j=0;j<=l2;++j)
		{
			if(!(i+j)) continue; LL tmp=0;
			if(i && j^l2) (tmp+=f[i-1][j]*p1%mod*dp2%mod)%=mod;
			if(j && i^l1) (tmp+=f[i][j-1]*dp1%mod*p2%mod)%=mod;
			if(i && j) (tmp+=f[i-1][j-1]*p1%mod*p2%mod)%=mod;
			f[i][j]=tmp*cp%mod;
 		}
 	for(int i=0;i<l2;++i) (ans+=f[l1][i])%=mod;
	printf("%lld\n",ans);
	
	return 0;
}