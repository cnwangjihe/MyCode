#include <bits/stdc++.h>

using namespace std;

const int MAXS = (1 << 10),
		  MAXM = 11,
		  MOD  = 1000000007;

int g[2][MAXS];
int f[MAXM][MAXS][2];
int cnt[MAXS],lim[MAXM];
int n,m,ans;

int main()
{
	freopen("2668.in","r",stdin);
	freopen("2668.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		m=0,ans=0;
		memset(g,0,sizeof g);
		memset(f,0,sizeof f);
		scanf("%d",&n);
		while (n)
		{
			lim[++m]=n%10;
			n/=10;
		}
		for (int i=1;i<=m/2;i++)
			swap(lim[i],lim[m-i+1]);
		f[0][0][1]=1;
		for (int i=0;i<m;i++)
		{
			f[i+1][0][0]=f[i][0][0]+f[i][0][1];
			for (int j=0;j<MAXS;j++)
				for (int k=(!j)?1:0;k<=9;k++)
				{
					f[i+1][j|(1<<k)][0]+=f[i][j][0];
					if (k>lim[i+1])
						continue;
					if (k==lim[i+1])
						f[i+1][j|(1<<k)][1]+=f[i][j][1];
					else 
						f[i+1][j|(1<<k)][0]+=f[i][j][1];
				}
		}
		for (int i=1;i<MAXS;i++)
			cnt[i]=f[m][i][0]+f[m][i][1];
		g[0][0]=1;
		int now=1;
		for (int i=1;i<MAXS;i++)
		{
			for (int j=0;j<MAXS;j++)
				g[now][j]=g[now^1][j];
			for (int j=0;j<MAXS;j++)
				if (!(j&i))
					(g[now][j+i]+=1ll*g[now^1][j]*cnt[i]%MOD)%=MOD;
			now^=1;
		}
		ans=0;
		for (int i=1;i<MAXS;i++)
			(ans+=g[now^1][i])%=MOD;
		printf("Case %d: %d\n",cn,ans);
	}
	return 0;
}