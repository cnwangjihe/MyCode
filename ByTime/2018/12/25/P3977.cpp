// Date    : 2018-12-25 10:51:39
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXS = 1<<7;

struct Matrix
{
	int n,m;
	unsigned int a[MAXS][MAXS];
	Matrix(int tn,int tm):n(tn),m(tm){memset(a,0,sizeof a);}
	void init()
	{
		for (int i=0;i<std::min(n,m);i++)
			a[i][i]=1;
		return ;
	}
	friend Matrix operator * (Matrix a,const Matrix& b)
	{
		if (a.m!=b.n)
			return Matrix(0,0);
		Matrix c(a.n,b.m);
		for (int i=0;i<a.n;i++)
			for (int j=0;j<b.m;j++)
				for (int k=0;k<a.m;k++)
					c.a[i][j]+=a.a[i][k]*b.a[k][j];
		return c;
	}
	unsigned int sum()
	{
		int ans=0;
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				ans+=a[i][j];
		return ans;
	}
};

int mp[3],a[MAXS];
int s[MAXS][3];
int n,m,p,k,cnt=0;

Matrix qpow(Matrix a,int k)
{
	Matrix ans(a.n,a.n);
	ans.init();
	for (int i=0;(1<<i)<=k;i++,a=a*a)
		if ((1<<i)&k)
			ans=ans*a;
	return ans;
}

int main()
{
//	freopen("P3977.in","r",stdin);
//	freopen("P3977.out","w",stdout);
	int t;
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for (int i=0;i<3;i++)
		for (int j=0;j<p;j++)
		{
			scanf("%d",&t);
			mp[i]|=(t<<j);
		}
	mp[1]^=(1<<k);
	for (int i=0;i<(1<<m);i++)
	{
		for (int j=0;j<m;j++)
		{
			if (!(i&(1<<j)))
				continue;
			s[i][0]|=(k>j)?(mp[0]>>(k-j)):(mp[0]<<(j-k));
			s[i][1]|=(k>j)?(mp[1]>>(k-j)):(mp[1]<<(j-k));
			s[i][2]|=(k>j)?(mp[2]>>(k-j)):(mp[2]<<(j-k));
		}
		if (!(s[i][1]&i))
			a[cnt++]=i;
	}
	Matrix b(cnt,cnt);
	int x,y;
	for (int i=0;i<cnt;i++)
	{
		x=a[i];
		for (int j=0;j<cnt;j++)
		{
			y=a[j];
			if ( (!(s[x][2]&y)) && (!(s[y][0]&x)) )
				b.a[i][j]=1;
		}
	}
	Matrix a(1,cnt);
	a.a[0][0]=1;
	printf("%u\n",(a*qpow(b,n)).sum());
	return 0;
}