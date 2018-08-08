#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 3009,
		  INF  = 1000000009;

char s1[MAXN],s2[MAXN];
int a[MAXN],b[MAXN];
int f[MAXN][MAXN][3];
int d[MAXN][MAXN];
int n,m,A,B;

int main()
{
	scanf("%s",s1);
	scanf("%s",s2);
	n=strlen(s1),m=strlen(s2);
	for (int i=0;i<n;i++)
		a[i+1]=((s1[i]=='A')?0:(s1[i]=='T')?1:(s1[i]=='G')?2:3);
	for (int i=0;i<m;i++)
		b[i+1]=((s2[i]=='A')?0:(s2[i]=='T')?1:(s2[i]=='G')?2:3);
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			scanf("%d",&d[i][j]);
	scanf("%d%d",&A,&B);
	for (int i=max(n,m);i;i--)
	{
		f[0][i][0]=f[i][0][0]=f[0][i][2]=f[i][0][1]=-(1LL<<30);
		f[0][i][1]=f[i][0][2]=-A-B*(i-1);
	}
	f[0][0][1]=f[0][0][2]=-(1LL<<30);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			f[i][j][0]=max(f[i-1][j-1][0],max(f[i-1][j-1][1],f[i-1][j-1][2]))+d[a[i]][b[j]];
			f[i][j][1]=max(max(f[i][j-1][0]-A,f[i][j-1][1]-B),f[i][j-1][2]-A);
			f[i][j][2]=max(max(f[i-1][j][0]-A,f[i-1][j][2]-B),f[i-1][j][1]-A);
		}
	printf("%d\n",max(f[n][m][0],max(f[n][m][1],f[n][m][2])));
	return 0;
}