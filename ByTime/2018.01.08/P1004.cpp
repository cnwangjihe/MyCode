#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int f[12][12][12][12];
int a[12][12];
int n,x,y,z;

int main()
{
	scanf("%d",&n);
	do
	{
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=z;
	}while (x|y|z);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				for(int l=1;l<=n;l++)
				{
					f[i][j][k][l]=max(max(f[i-1][j][k-1][l],f[i-1][j][k][l-1]),max(f[i][j-1][k-1][l],f[i][j-1][k][l-1]))+a[i][j]+a[k][l];
					if (i==k && l==j) f[i][j][k][l]-=a[i][j];
				}
			}
		}
	}
	printf("%d\n",f[n][n][n][n]);
	return 0;
}
