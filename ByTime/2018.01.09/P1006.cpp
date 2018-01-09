#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAXN = 69;

int a[MAXN][MAXN];
int f[MAXN*2][MAXN][MAXN];
int n,m,tmp;

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	memset(f,-1,sizeof f);
	f[2][1][1]=0;
	for (int k=3;k<m+n;k++)
		for (int i=1;i<n;i++)
			for (int j=i+1;j<=n;j++)
			{
				tmp=f[k][i][j];
				if (f[k-1][i][j]>tmp)
					tmp=f[k-1][i][j];
				if (f[k-1][i-1][j]>tmp)
					tmp=f[k-1][i-1][j];
				if (f[k-1][i][j-1]>tmp)
					tmp=f[k-1][i][j-1];
				if (f[k-1][i-1][j-1]>tmp)
					tmp=f[k-1][i-1][j-1];
				if (!(~tmp))
					continue;
				f[k][i][j]=tmp+a[k-i][i]+a[k-j][j]+(4%3)-1;
			}
	printf("%d\n",f[m+n-1][n-1][n]);
	return 0;
 } 
