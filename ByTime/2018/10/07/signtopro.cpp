#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5009;

int f[MAXN][MAXN][2];
int a[MAXN];
bool flag;
int n;

void solve1()
{
	for (int i=1;i<=n/2;i++)
		printf("%d ",i);
	if (n&1)
		printf("%d ",n/2);
	putchar('\n');
}

void solve2()
{
	memset(f,127,sizeof f);
	f[0][0][0]=f[1][0][0]=f[1][1][1]=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<=(n+1)/2;j++)
		{
			f[i+1][j][0]=min(f[i][j][0],f[i+1][j][0]);
			f[i+1][j][0]=min(f[i][j][1]+max(a[i+1]-a[i]+1,0),f[i+1][j][0]);
			f[i+2][j+1][1]=min(f[i][j][0]+max(a[i+1]-a[i+2]+1,0),f[i+2][j+1][1]);
			f[i+2][j+1][1]=min(f[i][j][1]+max(min(a[i]-1,a[i+1])-a[i+2]+1,0)+max(a[i+1]-a[i]+1,0),f[i+2][j+1][1]);
		}
	for (int i=1;i<=(n+1)/2;i++)
		printf("%d ",min(f[n][i][0],f[n][i][1]));
	putchar('\n');
	return ;
}

int main()
{
	freopen("signtopro.in","r",stdin);
	freopen("signtopro.out","w",stdout);
	flag=1;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (i-1 && a[i]!=a[i-1])
			flag=0;
	}
	if (flag)
		solve1();
	else
		solve2();
	return 0;
}