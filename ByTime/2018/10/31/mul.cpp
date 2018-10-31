#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509,
		  MAXS = (1<<11),
		  MOD  = 1000000007;

int f[32][32][MAXS];
bool g[MAXN];
int p[MAXN];
int n,k,cnt,Max,ans,m=0;

int GetStat(int x,int cnt)
{
	int s=0;
	for (int i=0;i<cnt;i++)
		s|=((x%p[i]==0)<<i);
	for (int i=0;i<cnt;i++)
		if (x%(p[i]*p[i])==0)
			return 0;
	return s;
}

int main()
{
	freopen("mul.in","r",stdin);
	freopen("mul.out","w",stdout);
	
	for (int i=2;i<=500;i++)
		if (!g[i])
		{
			p[m++]=i;
			for (int j=2;j*i<=500;j++)
				g[j*i]=1;
		}
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&n,&k);
		cnt=-1;Max=0;ans=0;
		while (p[++cnt]<=n);
	//	cerr << cnt << endl;
		memset(f,0,sizeof f);
		m=(1<<cnt);
		f[1][0][0]=1;
		int x,y,t;
		for (int i=2;i<=n;i++)
		{
			x=(i&1),y=(x^1);
			t=GetStat(i,cnt);
			if (t)
				Max++;
			for (int j=0;j<=min(k,Max);j++)
				for (int s=0;s<m;s++)
				{
					(f[x][j][s]+=f[y][j][s])%=MOD;
					if (t && j && ((s&t)==t))
						(f[x][j][s]+=f[y][j-1][s-t])%=MOD;
				}
			for (int j=0;j<=k;j++)
				for (int s=0;s<m;s++)
					f[y][j][s]=0;
		}
		for (int j=0;j<k;j++)
			for (int s=0;s<m;s++)
				(ans+=f[n&1][j][s])%=MOD;
		ans=(ans*2)%MOD;
		for (int s=0;s<m;s++)
			(ans+=f[n&1][k][s])%=MOD;
			
		ans=(ans-1+MOD)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}