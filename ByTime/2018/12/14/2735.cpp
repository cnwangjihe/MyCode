// Date    : 2018-12-14 12:11:24
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXD = 45,
		  MOD  = 1000000007;

int r[MAXD];
int fav[MAXN],fac[MAXN];
int n,d,ans,sum;
int f[MAXD][MAXD][MAXD*MAXD*3];

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

void init()
{
	fac[0]=fac[1]=1;
	for (int i=2;i<MAXN;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
	for (int i=MAXN-2;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	fav[0]=1;
	return ;
}

int C(int a,int b) {return (a<b || b<0)?0:1ll*fac[a]*fav[b]%MOD*1ll*fav[a-b]%MOD;}

int main()
{
	freopen("2735.in","r",stdin);
	freopen("2735.out","w",stdout);
	int T;
	init();
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&n,&d);
		ans=sum=0;
		memset(f,0,sizeof f);
		for (int i=1;i<=d;i++)
			scanf("%d",&r[i]),sum+=r[i];
		sort(r+1,r+d+1);
		f[0][0][0]=1;
		for (int i=0;i<d;i++)
			for (int j=0;j<=i;j++)
				for (int k=0;k<=sum*2;k++)
				{
					(f[i+1][j+1][k]+=f[i][j][k])%=MOD;
					if (j && k+r[i+1]<=sum*2)
						(f[i+1][j][k+r[i+1]]+=1ll*f[i][j][k]*j%MOD*2%MOD)%=MOD;
					if (j>1 && k+r[i+1]*2<=sum*2)
						(f[i+1][j-1][k+r[i+1]*2]+=1ll*f[i][j][k]*(j-1)%MOD*j%MOD)%=MOD;
				}
		for (int i=sum-r[1]+1;i<=sum*2;i++)
			(ans+=1ll*f[d][1][i-1]*C(n-i+d,d)%MOD)%=MOD;
		printf("%d\n",ans);
	}
	return 0;
}