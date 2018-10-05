#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009;

int on,om,n,m;
int a[MAXN][MAXN];
int f[2][MAXN][MAXN];

int main()
{
	scanf("%d%d",&on,&om);
	for (int i=1;i<=on;i++)
		for (int j=1;j<=om;j++)
			scanf("%d",&a[i*2][j*2]);
	n=on*2+3,m=om*2+3;
	for (int i=0;i<n;i++)
		a[i][m-1]=30,a[i][0]=31;
	for (int i=0;i<m;i++)
		a[n-1][i]=32,a[0][i]=33;
	int p;
	for (int j=1;j<n-1;j++)
	{
		p=2;
		f[0][j][2]=1;
		f[0][j][0]=f[0][j][1]=0;
		for (int i=3;i<m;i++)
		{
			f[0][j][i]=max(0,min(f[0][j][2*p-i],p+f[0][j][p]-i));
			while (a[j][i-f[0][j][i]-1]==a[j][i+f[0][j][i]+1])
				f[0][j][i]++;
			if (p+f[0][j][p]<i+f[0][j][i])
				p=i;
		}
	}
	for (int j=1;j<m-1;j++)
	{
		p=2;
		f[1][2][j]=1;
		f[1][0][j]=f[1][1][j]=0;
		for (int i=3;i<n;i++)
		{
			f[1][i][j]=max(0,min(f[1][2*p-i][j],p+f[1][p][j]-i));
			while (a[i-f[1][i][j]-1][j]==a[i+f[1][i][j]+1][j])
				f[1][i][j]++;
			if (p+f[1][p][j]<i+f[1][i][j])
				p=i;
		}
	}
	for (int i=1;i<n-1;i++)
	{
		for (int j=1;j<m-1;j++)
			cerr << f[0][i][j] << ' ';
		cerr << '\n';
	}
}