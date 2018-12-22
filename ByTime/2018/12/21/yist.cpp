// Date    : 2018-12-21 14:41:13
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std; //not suggest anymore.Please use std::

const long double eps=1e-10;
const int MAXT = 100000;

long double sum=0,p=1,q;
int n,MOD;
int cnt;

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
	freopen("yist.in","r",stdin);
	freopen("yist.out","w",stdout);
	scanf("%d%d",&n,&MOD);
	cnt=n*(n-1)/2;
	q=1.0*(cnt-(n-1))/cnt;
	for (int i=n-1;i<=MAXT;i++,p*=q)
		sum+=p*i;
	for (int i=1;i<=MAXT;i++)
		for (int j=1;j<=i && !(sum-1.0*i/j>eps);j++)
			if (abs(1.0*i/j-sum)<eps)
				return printf("%lld\n",1ll*i*qpow(j,MOD-2)%MOD),0;
	return 0;
}
