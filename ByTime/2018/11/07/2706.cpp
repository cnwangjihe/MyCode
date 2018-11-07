#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009;

bool mp[MAXN][MAXN];
int f[MAXN][MAXN];
int n,m;
long long ans=0;
char c;

int main()
{
	freopen("2706.in","r",stdin);
	freopen("2706.out","w",stdout);
	scanf("%d%d",&n,&m);
	bool fg=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			do {c=getchar();}
				while (c!='.' && c!='#');
			mp[i][j]=(c=='.');
			if (!mp[i][j])
				fg=0;
		}
		for (int j=m;j;j--)
			f[i][j]=mp[i][j]?f[i][j+1]+1:0;
	}
	int v;
	if (fg)
	{
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				v=f[i][j];
				ans+=(1ll*(1ll*v*(v+1)/2ll)*(1ll*i*(i+1)/2ll));
			//	cerr << ans << " " << f[i][j] << endl;
			}
		}
		printf("%lld\n",ans);
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			v=m;
			for (int k=i;k && v;k--)
			{
				v=min(v,f[k][j]);
				ans+=1ll*(1ll*v*(v+1)/2ll)*(i-k+1);
			}
		//	cerr << ans << " " << f[i][j] << endl;
		}
	}
	printf("%lld\n",ans);
	return 0;
}