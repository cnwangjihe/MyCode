#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

long long MOD,n,q,p,r,t,u,v,w,x,y,z,ans1=0,ans2=0,ans3=0;

long long mul(long long a,long long b)
{
	long long ans=0;
	for (long long i=0;(1ll<<i)<=b;i++,a=(a+a)%MOD)
		if (b&(1ll<<i))
			ans=(ans+a)%MOD;
	return ans;
}


struct Matrix
{
	long long v[11][11];
	int n;
	Matrix(){n=11;memset(v,0,sizeof v);}
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
			for (int k=0;k<n;k++)
			{
				if (v[i][k]==0ll)
					continue;
				for (int j=0;j<n;j++)
					ans.v[i][j]=(ans.v[i][j]+mul(v[i][k],a.v[k][j]))%MOD;
			}
		return ans;
	}
};

Matrix ans,a;

Matrix qpow(Matrix a,long long k)
{
	Matrix ans;
	ans.Reset();
	for (long long i=0;(1ll<<i)<=k;i++,a=a*a)
		if (k&(1ll<<i))
			ans=ans*a;
	return ans;
}

int main()
{
	scanf("%lld%lld",&n,&MOD);
	scanf("%lld%lld%lld%lld",&p,&q,&r,&t);
	scanf("%lld%lld%lld",&u,&v,&w);
	scanf("%lld%lld%lld",&x,&y,&z);

	int qw[] = \
	    {p ,q  ,1  ,0  ,1  ,0  ,0  ,0  ,r  ,t  ,1
		,1 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0
		,1 ,0  ,u  ,v  ,1  ,0  ,1  ,0  ,0  ,0  ,0
		,0 ,0  ,1  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0
		,1 ,0  ,1  ,0  ,x  ,y  ,0  ,1  ,0  ,1  ,2
		,0 ,0  ,0  ,0  ,1  ,0  ,0  ,0  ,0  ,0  ,0
		,0 ,0  ,0  ,0  ,0  ,0  ,w  ,0  ,0  ,0  ,0
		,0 ,0  ,0  ,0  ,0  ,0  ,0  ,z  ,0  ,0  ,0
		,0 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,1  ,2  ,1
		,0 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,1  ,1
		,0 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,1};
	for (int i=0;i<11;i++)
		for (int j=0;j<11;j++)
			a.v[i][j]=qw[i*11+j];
	int t[11]={3,1,3,1,3,1,w,z,1,1,1};
	Matrix ans=qpow(a,n-2);
	for (int i=0;i<11;i++)
		ans1=(ans1+mul(t[i],ans.v[0][i]))%MOD,
		ans2=(ans2+mul(t[i],ans.v[2][i]))%MOD,
		ans3=(ans3+mul(t[i],ans.v[4][i]))%MOD;
	printf("nodgd %lld\nCiocio %lld\nNicole %lld\n",ans1,ans2,ans3);
	return 0;
}
