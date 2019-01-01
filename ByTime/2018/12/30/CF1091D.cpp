// Date      : 2018-12-30 23:07:39
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1000009;
const long long MOD = 998244353;

long long fac[MAXN];
int n;
long long ans=0;

int main()
{
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	scanf("%d",&n);
	fac[1]=fac[0]=1;
	for (int i=2;i<=n;i++)
		fac[i]=fac[i-1]*(1ll*i)%MOD;

	long long tmp=1;
	for (int i=1;i<n;i++)
	{
		tmp=tmp*(n-i+1)%MOD;
		(ans+=tmp*(fac[n-i]-1ll)%MOD)%=MOD;
	}
	printf("%lld\n",(ans+fac[n])%MOD);
	return 0;
}