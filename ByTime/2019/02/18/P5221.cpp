// Date      : 2019-02-18 11:42:01
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P5221
// Algorithm : 简单数论
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1000009,
		  MOD  = 104857601;

int f[MAXN],p[MAXN];
bool notp[MAXN];
int sum=1,ans=1,n,m=0;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if (k&(1<<i))
			ans=1ll*ans*a%MOD;
	return ans;
}

int main()
{
//	freopen("P5221.in","r",stdin);
//	freopen("P5221.out","w",stdout);
	scanf("%d",&n);
	f[1]=1;
	for (int i=2;i<=n;i++)
	{
		sum=1ll*sum*i%MOD;
		if (!notp[i])
			p[m++]=i,f[i]=i-1;
		for (int j=0;j<m;j++)
		{
			if (p[j]*i>n)
				break;
			notp[p[j]*i]=1;
			if (i%p[j]==0)
			{
				f[i*p[j]]=f[i]*p[j];
				break;
			}
			f[i*p[j]]=f[p[j]]*f[i];
		}
	}
	for (int i=1;i<=n;i++)
		f[i]=f[i]*2+f[i-1]%(MOD-1);
	for (int i=2;i<=n;i++)
		ans=1ll*ans*qpow(i,f[n/i]-1)%MOD;
	ans=(1ll*qpow(sum,2*n)*qpow(1ll*ans*ans%MOD,MOD-2))%MOD;
	printf("%d\n",ans);
	return 0;
}