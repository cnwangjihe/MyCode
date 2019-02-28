// Date      : 2019-02-23 11:21:55
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MOD  = 1000000007,
		  MAXN = 59,
		  MAXV = 10009;

int n,m,k;
int f[MAXN][MAXN];
int fav[MAXV],fac[MAXV];

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

inline int C(int n,int m) {return (n<m || m<0)?0:1ll*fac[n]*fav[m]%MOD*fav[n-m]%MOD;}

void init()
{
	fac[0]=fav[0]=1;
	for (int i=1;i<MAXV;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXV-1]=qpow(fac[MAXV-1],MOD-2);
	for (int i=MAXV-2;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	f[1][0]=1;
	for (int i=2;i<=50;i++)
		for (int j=i-1;j<=min(C(i,2),50);j++)
		{
			f[i][j]=C(C(i,2),j);
			for (int a=1;a<=i-1;a++)
				for (int b=a-1;b<=min(C(a,2),j);b++)
					f[i][j]=(1ll*f[i][j]-1ll*f[a][b]*C(C(i-a,2),j-b)%MOD*C(i-1,a-1)%MOD+MOD)%MOD;
		}
	return ;
}

void Solve0()
{
	printf("%d\n",f[n][k]);
	return ;
}

void Solve1()
{
	int ans=0;
	ans=(ans+1ll*f[n-1][k-1]*(k-1)%MOD)%MOD;
	ans=(ans+1ll*f[n-1][k-2]*(k-2)%MOD)%MOD;
	printf("%d\n",ans);
	return ;
}

inline int Getf(int n,int m) {return m<0?0:f[n][m];}

void Solve2()
{
	int ans=0;
	ans=(ans+1ll*Getf(n-2,k-2)*(k-2)%MOD*(k-3)%MOD)%MOD;
	ans=(ans+2ll*Getf(n-2,k-3)*(k-3)%MOD*(k-4)%MOD)%MOD;
	ans=(ans+1ll*Getf(n-2,k-4)*(k-4)%MOD*(k-5)%MOD)%MOD;
	ans=(ans+2ll*Getf(n-2,k-3)*(k-3)%MOD)%MOD;
	ans=(ans+2ll*Getf(n-2,k-2)*(k-2)%MOD)%MOD;
	ans=(ans+1ll*Getf(n-2,k-4)*(k-4)%MOD)%MOD;
	ans=(ans+1ll*Getf(n-2,k-3)*(k-3)%MOD)%MOD;
	ans=(ans+1ll*Getf(n-2,k-3)*(n-2)%MOD)%MOD;
	printf("%d\n",ans);
	return ;
}

int main()
{
	freopen("2807.in","r",stdin);
	freopen("2807.out","w",stdout);
	init();
	int T;
	for (scanf("%d",&T);T;T--)
	{
		scanf("%d%d%d",&n,&m,&k);
		if (m==0)
			Solve0();
		if (m==1)
			Solve1();
		if (m==2)
			Solve2();
	}
}