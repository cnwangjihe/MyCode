#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009;

int f[MAXN][MAXN][2][2];
int a[MAXN];
int n,m;
int ans=-1;

int main()
{
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
	memset(f,-1,sizeof f);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]+=1000;
	f[1][0][0][0]=0;
	f[1][1][1][1]=a[1];
	for (int i=1;i<n;i++)
		for (int j=0;j<=m;j++)
		{
			if (~f[i][j][0][0])
				f[i+1][j+1][1][0]=f[i][j][0][0]+a[i+1];
			if (~f[i][j][0][1])
				f[i+1][j+1][1][1]=f[i][j][0][1]+a[i+1];

			f[i+1][j][0][0]=max(max(f[i][j][0][0],f[i][j][1][0]),f[i+1][j][0][0]);
			f[i+1][j][0][1]=max(max(f[i][j][0][1],f[i][j][1][1]),f[i+1][j][0][1]);
		}
	ans=max(f[n][m][1][0],max(f[n][m][0][1],f[n][m][0][0]));
/*
	for (int i=1;i<n;i++)
	{
		for (int j=1;j<=m;j++)
			cerr << f[i][j][0][0] << ' ' << f[i][j][0][1] << "  ";
		cerr << '\n';
	}
*/
	if (~ans)
		printf("%d\n",ans-(m*1000));
	else
		printf("unbdd!\n");
	return 0;
}