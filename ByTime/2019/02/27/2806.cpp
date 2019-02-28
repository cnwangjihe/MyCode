// Date      : 2019-02-27 18:47:26
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 28,
		  MOD  = 1000000007;

int f[MAXN][MAXN][MAXN][MAXN][MAXN*2];
int g[MAXN][MAXN*2][MAXN*2],s[MAXN][MAXN][MAXN*2];
int fav[100],fac[100];
int n,ans;

void solve1()
{
	memset(f,0,sizeof f);
	memset(s,0,sizeof s);
	f[0][0][0][0][0]=1;
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)
			for (int k=0;k<26;k++)
				for (int c1=0;c1<26;c1++)
					for (int c2=0;c2<51;c2++)
					{
						if (!f[i][j][k][c1][c2])
							continue;
						if (!k)
							(s[i][c1][c2]+=f[i][j][k][c1][c2])%=MOD;
						(f[i][j][k+1][c1+1][c2]+=f[i][j][k][c1][c2])%=MOD;
						if (k+1<=j)
							(f[i][j][k+1][c1][c2+1]+=f[i][j][k][c1][c2])%=MOD;
						(f[i+1][max(j,k)][0][c1][c2]+=f[i][j][k][c1][c2])%=MOD;
					}
}

void solve2(int s1,int s2)
{
	memset(g,0,sizeof g);
	g[0][0][0]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<=s1;j++)
			for (int k=0;k<=s2;k++)
				for (int c1=0;c1+j<=s1;c1++)
					for (int c2=0;c2+k<=s2;c2++)
						(g[i+1][j+c1][k+c2]+=1ll*g[i][j][k]*s[n][c1][c2]%MOD)%=MOD;
}

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
	fac[0]=fav[0]=1;
	for (int i=1;i<60;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[59]=qpow(fac[59],MOD-2);
	for (int i=58;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	return ;
}

inline int C(int n,int m)
{
	return (m>n || m<0) ? 0 : 1ll*fac[n]*fav[m]%MOD*fav[n-m]%MOD;
}

int main()
{
	freopen("2806.in","r",stdin);
	freopen("2806.out","w",stdout);
	int T;
	scanf("%d",&T);
	init();
	solve1();
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		int R,G,B;
		scanf("%d%d%d%d",&R,&G,&B,&n);
		solve2(R,G+B);
		(ans+=1ll*g[n][R][G+B]*C(G+B,G)%MOD)%=MOD;
		solve2(G,R+B);
		(ans+=1ll*g[n][G][R+B]*C(R+B,R)%MOD)%=MOD;
		solve2(B,G+R);
		(ans+=1ll*g[n][B][G+R]*C(G+R,R)%MOD)%=MOD;
		printf("%d\n",ans);
	}
	return 0;
}