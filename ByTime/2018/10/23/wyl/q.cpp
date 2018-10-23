#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009,
		  MOD  = 1000000007;

int f[MAXN][MAXN];
int n,ans;

int main()
{
	freopen("q.in","r",stdin);
	freopen("q.out","w",stdout);

	memset(f,0,sizeof f);
	scanf("%d",&n);

	long long v;
	f[1][0]=1;
	for (int i=1;i<n;i++)
	{
		for (int j=0;j<i;j++)
		{
			v=2ll*i-1ll-j;
			(f[i+1][j]+=(1ll*f[i][j]*v%MOD*1ll*(v-1ll)%MOD + 2ll*f[i][j]*j%MOD)%MOD)%=MOD;
			(f[i+1][j+1]+=2ll*f[i][j]*v%MOD)%=MOD;
			if (j>1)
				(f[i+1][j-2]+=1ll*f[i][j]*j%MOD*1ll*(j-1)%MOD)%=MOD;
			if (j)
				(f[i+1][j-1]+=2ll*f[i][j]*j%MOD*1ll*v%MOD)%=MOD;
		}
	}
	ans=(1ll*f[n][1]+1ll*f[n][0]*max((2*n-3),0)%MOD)%MOD;
	printf("%d\n",ans);
	return 0;
}