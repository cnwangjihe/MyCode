#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const long long MOD = 1000000007ll;

struct Matrix
{
	long long v[4][4];
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

long long n;
Matrix ans,a;
long long b[4];
long long sum;

Matrix qpow(Matrix a,long long k)
{
	Matrix ans;
	ans.Reset();
	for (long long i=0;(1ll<<i)<=k;i++,a=a*a)
		if ((1ll<<i)&k)
		{
			ans=ans*a;
		}
	return ans;
}

int main()
{
	freopen("big.in","r",stdin);
	freopen("big.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	a.v[0][2]=a.v[1][0]=a.v[2][1]=a.v[2][2]=1;
	for (;ttt--;)
	{
		sum=0;
		scanf("%I64d",&n);
		ans=qpow(a,n-1);
		b[0]=2,b[1]=3,b[2]=4;
		for (int i=0;i<3;i++)
			sum=(sum+(b[i]*ans.v[i][0]%MOD))%MOD;
		printf("%I64d\n",sum);
	}
	return 0;
}