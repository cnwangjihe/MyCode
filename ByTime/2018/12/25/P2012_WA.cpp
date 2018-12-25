// Date    : 2018-12-25 08:29:58
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 10;
const long long MOD = 1000000000ll;

struct Matrix
{
	int n,m;
	long long a[MAXN][MAXN];
	Matrix(int tn=0,int tm=0):n(tn),m(tm){memset(a,0,sizeof a);}
	void init()
	{
		for (int i=0;i<std::min(n,m);i++)
			a[i][i]=1;
		return ;
	}
	friend Matrix operator * (Matrix a,const Matrix &b)
	{
		if (a.m!=b.n)
			return Matrix(0,0);
		Matrix c(a.n,b.m);
		for (int i=0;i<a.n;i++)
			for (int j=0;j<b.m;j++)
				for (int k=0;k<a.m;k++)
					(c.a[i][j]+=a.a[i][k]*b.a[k][j]%MOD)%=MOD;
		return c;
	}
};

long long n;

Matrix qpow(Matrix a,long long k)
{
	Matrix ans(a.n,a.n);
	ans.init();
	for (int i=0;(1ll<<i)<=k;i++,a=a*a)
		if ((1ll<<i)&k)
			ans=ans*a;
	return ans;
}

int main()
{
//	freopen("P2012.in","r",stdin);
//	freopen("P2012.out","w",stdout);
	Matrix b(4,4);
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			if (i+j!=3)
				b.a[i][j]=4;
	while (scanf("%lld",&n) && n)
	{
		Matrix a(1,4);
		a.a[0][0]=1;
		Matrix c=a*qpow(b,n);
		long long ans=c.a[0][2];
		printf("%lld\n",ans);
	}
	return 0;
}