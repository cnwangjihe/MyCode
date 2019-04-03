// Date      : 2019-04-01 21:13:25
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : http://10.3.35.134/showproblem?id=2845
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009,
		  MOD  = 1000000007;

int x[MAXN*2],y[MAXN*2];
int inv[33];
int n;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

void Init()
{
	for (int i=1;i<=30;i++)
		inv[i]=qpow((1<<i),MOD-2);
	return ;
}

int main()
{
	freopen("2845.in","r",stdin);
	freopen("2845.out","w",stdout);
	int T,m,sx,sy;
	Init();
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&n);
		x[1]=1;
		for (int i=1;i<=2*n-1;i++)
		{
			m=log2(i)+1;
			sx=0,sy=0;
			for (int j=2;j<=m;j++)
				(sx+=1ll*inv[j]*(x[i-(1<<(j-1))+2])%MOD)%=MOD,
				(sy+=1ll*inv[j]*(y[i-(1<<(j-1))+2]+j)%MOD)%=MOD;
			x[i+1]=((2ll*(x[i]-sx)%MOD)+MOD)%MOD;
			y[i+1]=(2ll*(y[i]-sy-1ll*m*inv[m]%MOD)%MOD-1+MOD)%MOD;
		}
		int tmp=1ll*y[n*2]*qpow(x[n*2],MOD-2)%MOD;
		tmp=MOD-tmp;
		printf("%lld\n",(1ll*x[n]*tmp%MOD+y[n])%MOD);
	}
	return 0;
}