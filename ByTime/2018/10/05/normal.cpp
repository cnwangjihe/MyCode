#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

int n,m;
long long ans=0;
int a[MAXN][MAXN],b[MAXN][MAXN],c[MAXN][MAXN];

int main()
{
	freopen("normal.in","r",stdin);
	freopen("normal.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			b[i][j]=max(0,a[i][j]-a[i][j-1]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			c[i][j]=max(0,b[i][j]-b[i-1][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			ans=ans+1ll*c[i][j];
	printf("%lld\n",ans);
	return 0;
}