// Date      : 2018-12-28 14:38:57
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1000000009,
		  MAXC = 10009,
		  MOD  = 998244353;

int f[2][MAXC];
int n,m,c,invc;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

int main()
{
//	freopen("chocolate.in","r",stdin);
//	freopen("chocolate.out","w",stdout);
	scanf("%d%d%d",&n,&c,&m);
	if ((n&1)^(m&1))
		return printf("0\n"),0;
	f[0][0]=1;
	invc=qpow(c,MOD-2);
	int d;
	for (int i=0;i<n;i++)
	{
		d=i&1;
		for (int j=0;j<=c;j++)
		{
			if (j)
				(f[d^1][j-1]+=1ll*f[d][j]*j%MOD)%=MOD;
			if (j!=c)
				(f[d^1][j+1]+=1ll*f[d][j]*(c-j)%MOD)%=MOD;
			f[d][j]=0;
		}
	}
	printf("%lld\n",1ll*f[n&1][m]*qpow(invc,n)%MOD);
	return 0;
}