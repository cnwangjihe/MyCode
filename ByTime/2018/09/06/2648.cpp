#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009,
		  MOD  = 1000000007;

int f[MAXN][MAXN][16];
int g[MAXN],fac[MAXN],fav[MAXN];
int n,m,sum;

void _out(int s)
{
	for (int i=0;i<4;i++)
		if ((1<<i)&s)
			putchar('1');
		else
			putchar('0');
	putchar('\n');
	return ;
}

inline void _debug(int s,int ns)
{
	_out(s);
	_out(ns);
	putchar('\n');
	return ;
}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=(1ll*a*a)%MOD)
		if (k&(1<<i))
			ans=(1ll*ans*a)%MOD;
	return ans;
}

inline int C(int a,int b)
{
	return (a<b)?0:(1ll*fac[a]*fav[b]%MOD*1ll*fav[a-b]%MOD);
}

int main()
{
	freopen("2648.in","r",stdin);
	freopen("2648.out","w",stdout);
	int T;
	scanf("%d",&T);
	memset(f,0,sizeof f);
	f[0][0][0]=1;
	int ns;
	for (int i=0;i<=2000;i++)
		for (int j=0;j<=i;j++)
			for (int s=0;s<(1<<4);s++)
			{
				if (!f[i][j][s])
					continue;
				ns=(s&3)^((s&8)>>1);
			//	_debug(s,ns);
				(f[i+1][j][ns]+=f[i][j][s])%=MOD;
				for (int p=i;p<=i+2;p++)
				{
					if ( (p==i && (s&4)) || (p==i+1 && (s&8)) || (p==1 && (s&1)) || (p==0 && (s&2)) )
						continue;
					ns=(s&3)^((s&8)>>1);
					if (p==i+1)
						ns|=4;
					if (p==i+2)
						ns|=8;
					if (p==1)
						ns|=1;
					if (p==0)
						ns|=2;
			//		_debug(s,ns);
					(f[i+1][j+1][ns]+=f[i][j][s])%=MOD;
				}
			//	cerr << "-------------------------------\n";
			}
	fac[0]=1;
	for (int i=1;i<MAXN;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
	for (int i=MAXN-2;i>=0;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&n,&m);
		memset(g,0,sizeof g);
		for (int i=0;i<=n;i++)
		{
			for (int j=0;j<(1<<4);j++)
				if (f[n][i][j] && !( ((j&8) && (j&1)) || ((j&4)&&(j&2)) ))
					(g[i]+=f[n][i][j])%=MOD;
			g[i]=1ll*fac[n-i]*g[i]%MOD;
		}
		for (int i=n;~i;i--)
			for (int j=i+1;j<=n;j++)
				g[i]=(g[i]+MOD-1ll*g[j]*C(j,i)%MOD)%MOD;
		
		int ans=0;
		for (int i=m;i<=n;i++)
			(ans+=g[i])%=MOD;
		
		printf("Case %d: %d\n",cn,ans);
	}
	return 0;
}