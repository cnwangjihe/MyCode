#include <bits/stdc++.h>

using namespace std;

const long long MOD = 998244353;

long long qpow(long long a,long long k)
{
	long long ans=1;
	for (long long i=0;(1ll<<i)<=k;i++,a=((long long)a*a)%MOD)
		if (k&(1ll<<i))
			ans=((long long)ans*a)%MOD;
	return ans;
}

const int MAXN = 2009;

long long l1,l2,p1,p2;
long long P1,P2,P3,P4,t;
long long f[MAXN][MAXN];
long long ans=0;

int main()
{
	freopen("2624.in","r",stdin);
	freopen("2624.out","w",stdout);
	scanf("%lld%lld%lld%lld",&l1,&l2,&p1,&p2);
	P1=qpow(p1,MOD-2),P2=qpow(p2,MOD-2);
	P3=(1ll+MOD-P1)%MOD,P4=(1ll+MOD-P2)%MOD;
	f[0][0]=1;
	t=qpow((1ll+MOD-(P3*P4)%MOD)%MOD,MOD-2);
//	cerr << t << endl;
	for (int i=0;i<=l1;i++)
		for (int j=0;j<=l2;j++)
		{
			if (!i && !j)
				continue;
			if (i && j!=l2)
				f[i][j]+=P1*P4%MOD*f[i-1][j]%MOD;
			if (j && i!=l1)
				f[i][j]+=P3*P2%MOD*f[i][j-1]%MOD;
			if (i && j)
				f[i][j]+=P1*P2%MOD*f[i-1][j-1]%MOD;
			f[i][j]=f[i][j] %MOD *t %MOD;
		}
 	for (int i=0;i<l2;i++) 
 		ans+=f[l1][i],ans%=MOD;
	printf("%lld\n",ans);
	return 0;
}