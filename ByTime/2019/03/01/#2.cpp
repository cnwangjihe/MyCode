#include<bits/stdc++.h>
using namespace std ;

const int mod=1e9+7,N=305,K=5e6+10;
int n,m,k,w[N],fac[K*2],ifac[K*2],t[K],tmp[K],ans;

int qpow(int x,int y)
{
	int ret=1;
	for (;y;y>>=1,x=1ll*x*x%mod)
		if (y&1) ret=1ll*ret*x%mod;
	return ret;
}

void init()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=m;i++) scanf("%d",&w[i]); sort(w+1,w+1+m); fac[0]=ifac[0]=1;
	for (int i=1;i<=k+n;i++) fac[i]=1ll*fac[i-1]*i%mod; ifac[k]=qpow(fac[k],mod-2);
	for (int i=k-1;i>=1;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}

int C(int x,int y)
{
	if (y>x||y<0) return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

void add(int x,int y)
{
	if (x<0) return; x++;
	for (;x<=k;x+=x&-x) {t[x]+=y;if(t[x]>=mod)t[x]-=mod;}
}

int sum(int x)
{
	if (x<0) return 0; x++; int ret=0;
	for (;x;x-=x&-x) {ret+=t[x];if(ret>=mod)ret-=mod;}
	return ret;
}

void solve()
{
	int R=w[1],now;
	for (int i=0;i<=w[1];i++) add(i,1);
	for (int i=2;i<=m;i++)
	{
		for (int j=1;j<=R;j++) tmp[j]=(sum(j-1)-sum(j-w[i]-1)+mod)%mod;
		for (int j=R+1;j<=R+w[i];j++) tmp[j]=(sum(R)-sum(j-w[i]-1)+mod)%mod;
		for (int j=1;j<=R+w[i];j++) add(j,tmp[j]); R+=w[i]; if (R>k) R=k;
	}
	if (n==m) {printf("%d\n",(sum(k)-sum(k-1)+mod)%mod);return;}
	for (int i=0;i<=R;i++)
	{
		now=sum(i)-sum(i-1);if(now<0)now+=mod;
		ans=ans+1ll*now*C((k-i)+(n-m)-1,(n-m)-1)%mod;
		if (ans>=mod) ans-=mod;
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
