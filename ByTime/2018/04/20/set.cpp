#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 100009;
const long long MOD = 10000007ll;

struct Matrix
{
	long long v[3][3];
	int n;
	Matrix()
	{
		memset(v,0,sizeof v);
		n=3;
	}
	void Reset()
	{
		for (int i=0;i<n;i++)
			v[i][i]=1;
		return ;
	}
	Matrix operator *(const Matrix &a)
	{
		Matrix ans;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				for (int k=0;k<n;k++)
					ans.v[i][j] += (v[i][k] * a.v[k][j]) % MOD,
					ans.v[i][j] %= MOD;
		return ans;
	}   
};

long long k,sum=0,ans=0;
int n;
long long a[MAXN];

Matrix qpow(Matrix a,long long k)
{
	Matrix ans;
	ans.Reset();
	for (int i=0;(1ll<<i)<=k;i++,a=a*a)
		if (k&(1ll<<i))
			ans=ans*a;
	return ans;
}

int main()
{
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	scanf("%d%I64d",&n,&k);
	for (int i=0;i<n;i++)
		scanf("%I64d",&a[i]),sum+=a[i]+MOD,sum%=MOD;
	sort(a,a+n);
	if (a[n-1]<0)
		return printf("%I64d\n",((sum+(a[n-1]+a[n-2]+MOD)*k)%MOD)%MOD)&0;
	a[n-2]=(a[n-2]+MOD)%MOD;
	Matrix b;
	b.v[0][1]=b.v[1][0]=1ll;
	b.v[1][1]=b.v[0][2]=b.v[2][2]=1ll;
//	b=b*b;
//	b=b*b;
	b=qpow(b,k);
//	for (int i=0;i<3;i++)
//	{
//		for (int j=0;j<3;j++)
//			printf("%d ",b.v[i][j]);
//		putchar('\n');
//	}
	int f[3]={(a[n-1]+a[n-2])%MOD,(a[n-1]+a[n-1]+a[n-2])%MOD,0};
	for (int i=0;i<3;i++)
		ans+=f[i]*b.v[i][2];
	printf("%I64d\n",(ans+sum)%MOD);
	return 0;
}