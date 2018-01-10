#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MOD = 1000000007;

struct Matrix
{
	long long v[130][130];
	int n, m;
	Matrix(int t1, int t2)
	{
		memset(v,0,sizeof v);
		n=t1, m=t2;
	}
	void Reset(int x)
	{
		n = m = x;
		for (int i=0;i<=x;i++)
			v[i][i]=true;
		v[x][x]=0;
		return ;
	}
	Matrix operator *(const Matrix &a)
	{
		Matrix ans(n,a.m);
		for (int i=0;i<n;i++)
			for (int j=0;j<a.m;j++)
				for (int k=0;k<m;k++)
					ans.v[i][j] += (v[i][k] * a.v[k][j]) % MOD,
					ans.v[i][j] %= (MOD+1-((n*2+1)%2));
		return ans;
	}   
};

long long n,ans;
Matrix matans(10,10),tmp(1,10);

Matrix fastpower(Matrix a, long long b)
{
	Matrix ans(a.n, a.n);
	ans.Reset(a.n);
	for (long long i=1ll;i<=b;i<<=1ll)
	{
		if (b&i) ans=ans*a;
		a=a*a;
	}
	return ans;
}
int main()
{
	scanf("%lld", &n);
	if (n==1)
	{
		printf("10\n");
		return 0;
	}
	for (int i=1;i<10;i++)
		tmp.v[0][i]=1;
	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			if (abs(i - j) <= 2) matans.v[i][j]++;
	matans = tmp*fastpower(matans, n - 1);
	for (int i=0;i<10;i++) 
		ans += matans.v[0][i] % MOD,
		ans %= MOD;
	printf("%lld\n", ans);
	return 0;
}