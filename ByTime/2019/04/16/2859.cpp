// Date      : 2019-04-16 09:13:59
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 59;
const long double eps = 1e-13;

inline long double qpow(long double a,int k)
{
	long double ans=1;
	for (int i=0;(1<<i)<=k;i++,a*=a)
		if ((1<<i)&k)
			ans*=a;
	return ans;
}

int n,p;
long long C[MAXN][MAXN];
long double f[MAXN][MAXN][MAXN][2];
long double ans;

void init()
{
	for (int i=0;i<MAXN;i++)
		C[i][0]=C[i][i]=1;
	for (int i=1;i<MAXN;i++)
		for (int j=1;j<i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	return ;
}

int main()
{
	freopen("2859.in","r",stdin);
	freopen("2859.out","w",stdout);
	init();
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&p,&n);
		memset(f,0,sizeof f);
		if (n==1)
		{
			printf("0\n");
			continue;
		}
		for (int i=0;i<=p;i++)
			f[1][i][i][0]=1.0*C[p][i]*qpow(n-1,p-i)/qpow(n,p);
		long double t;
		for (int i=1;i<n;i++)
			for (int j=0;j<=p;j++)
				for (int k=0;k<=j;k++)
				{
					if (f[i][j][k][0]<eps && f[i][j][k][1]<eps)
						continue;
					for (int d=0;d<=p-j;d++)
					{
						t=1.0*C[p-j][d]*qpow(n-i-1,p-j-d)/qpow(n-i,p-j);
						if (d>k)
							f[i+1][j+d][d][0]+=1.0*t*(f[i][j][k][0]+f[i][j][k][1]);
						if (d==k)
							f[i+1][j+d][k][1]+=1.0*t*(f[i][j][k][0]+f[i][j][k][1]);
						if (d<k)
						{
							f[i+1][j+d][k][0]+=1.0*t*f[i][j][k][0];
							f[i+1][j+d][k][1]+=1.0*t*f[i][j][k][1];
						}
					}
				}
		ans=0;
		for (int i=0;i<=p;i++)
			ans+=f[n][p][i][0];
		printf("%.12Lf\n",1.0-ans);
	}
	return 0;
}