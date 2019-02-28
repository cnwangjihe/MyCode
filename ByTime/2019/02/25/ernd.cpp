// Date      : 2019-02-25 19:04:35
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 309,
		  MAXV = MAXN;

int C[MAXV][MAXV];
int h[MAXN],f[MAXN],g[MAXN][MAXN];
int n,m,Mod,pMod,ans=0;

int qpow(int a,int k,int Mod)
{
	int ans=1;
	for (int i=0;(1ll<<i)<=k;i++,a=1ll*a*a%Mod)
		if ((1<<i)&k)
			ans=1ll*ans*a%Mod;
	return ans;
}

int Phi(int v)
{
	int phi=v;
	for (int i=2;i*i<=v;i++)
		if(!(v%i))
		{
			phi/=i,phi*=i-1;
			while (!(v%i))
				v/=i;
		}
	if (v!=1)
		phi/=v,phi*=v-1;
	return phi;
}

void init()
{
	C[0][0]=1;
	for (int i=1;i<MAXV;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}
	pMod=Phi(Mod);
	return ;
}

int main()
{
	freopen("ernd.in","r",stdin);
	freopen("ernd.out","w",stdout);
	scanf("%d%d%d",&n,&m,&Mod);
	init();
	for (int i=1;i<=n;i++)
	{
		if (i>=30 || (1<<i)-1>pMod)
			h[i]=qpow(2,qpow(2,i,pMod)+pMod-1,Mod);
		else
			h[i]=qpow(2,(1<<i)-1,Mod);
		for (int j=1;j<i;j++)
			(h[i]-=1ll*h[j]*C[i][j]%Mod)%=Mod;
		h[i]--;
		h[i]=h[i]<0?h[i]+Mod:h[i];
	}
	for (int i=1;i<=n;i++)
	{
		f[i]=h[i];
		for (int j=1;j<i;j++)
			(f[i]-=1ll*f[j]*h[i-j]%Mod*C[i-1][j-1]%Mod)%=Mod;
		f[i]=f[i]<0?f[i]+Mod:f[i];
	}
	for (int i=1;i<=n;i++)
	{
		g[i][1]=f[i];
		for (int j=2;j<=i;j++)
		{
			g[i][j]=0;
			for (int k=1;k<i;k++)
				(g[i][j]+=1ll*f[k]*g[i-k][j-1]%Mod*C[i-1][k-1]%Mod)%=Mod;
		}
	}
	for (int i=m;i<=n;i++)
		(ans+=1ll*g[i][m]*C[n][i]%Mod)%=Mod;
	printf("%d\n",ans);
	return 0;
}