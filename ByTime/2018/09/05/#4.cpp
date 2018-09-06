#include<bits/stdc++.h>
using namespace std;
#define N 2050
#define mod 1000000007

int f[N][N][16],ans[N],fac[N],rev[N];

int Pow(int x,int y)
{
	if  (y==0) return 1;
int t=Pow(x,y/2);
	if  (y&1) return 1ll*t*t%mod*x%mod;
	return 1ll*t*t%mod;
}

int C(int n,int m)
{
	if  (n<m) return 0;
	return 1ll*fac[n]*rev[m]%mod*rev[n-m]%mod;
}
void _out(int s)
{
	for (int i=3;~i;i--)
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


int main()
{
int cas,dt,i,j,k,t,news,n,m;
//	freopen("2648.in","r",stdin);
//	freopen("2648.out","w",stdout);
	for (fac[0]=i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	rev[N-1]=Pow(fac[N-1],mod-2);
	for (i=N-2;i>=0;i--) rev[i]=1ll*rev[i+1]*(i+1)%mod;
	
	n=2000;
	f[0][0][0]=1;
	for (i=0;i<4;i++)
		for (j=0;j<=i;j++)
			for (k=0;k<1<<4;k++)
			if  (f[i][j][k])
			{
				news=(k&12)|((k&1)<<1);
				_debug(k,news);
				f[i+1][j][news]+=f[i][j][k];
				if  (f[i+1][j][news]>=mod) f[i+1][j][news]-=mod;
				for (t=i;t<=i+2;t++)
				{
					if  ((t==1&&(k&8))||
						(t==0&&(k&4))||
						(t==i&&(k&2))||
						(t==i+1&&(k&1))) continue;
					news=(k&12)|((k&1)<<1);
					_debug(k,news);
					if  (t==1) news|=8;
					if  (t==0) news|=4;
					if  (t==i+1) news|=2;
					if  (t==i+2) news|=1;
					f[i+1][j+1][news]+=f[i][j][k];
					if  (f[i+1][j+1][news]>=mod) f[i+1][j+1][news]-=mod;
				}
				cerr << "-------------------------------\n";
			}
	
	
	
	scanf("%d",&cas);
	for (dt=1;dt<=cas;dt++)
	{
		scanf("%d%d",&n,&m);
		memset(ans,0,sizeof(ans));
		for (i=0;i<=n;i++)
		{
			for (j=0;j<1<<4;j++)
			if  (f[n][i][j])
			{
				if  ((j&8)&&(j&1)) continue;
				if  ((j&4)&&(j&2)) continue;
				(ans[i]+=f[n][i][j])%=mod;
			}
			ans[i]=1ll*fac[n-i]*ans[i]%mod;
		}
			
		for(int i=n; i>=0; --i)
		for(int j=i+1; j<=n; ++j)
			ans[i]=(ans[i]-1ll*ans[j]*C(j,i))%mod;
		
		int sum=0;
		for(int i=m; i<=n; ++i) (sum+=ans[i])%=mod;
		printf("Case %d: %d\n",dt,(sum%mod+mod)%mod);
	} 
}
