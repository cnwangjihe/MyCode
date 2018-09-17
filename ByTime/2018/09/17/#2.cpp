#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define mkp make_pair
#define fi first
#define se second
using namespace std;

typedef long long LL;
const int mod=1e9+7,N=1e5+10;
int sz,n,rt,siz[N],pos[N],a[N];
LL inv[N];
pair<int,pair<int,int> > tr[N];

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return ret;
}

void init()
{
	sz=0;
	for(int i=0;i<=n+1;++i) tr[i]=mkp(0,mkp(0,0)),siz[i]=0,pos[i]=0;
}

void build()
{
	rt=0;int pre=0,t=0;
	for(int i=1;i<=n;++i)
	{
		while(t && tr[pos[t]].fi<a[i]) pre=pos[t--];
		tr[++sz].fi=a[i];
		if(!t) rt=sz; else tr[pos[t]].se.se=sz;
		tr[sz].se.fi=pre;pos[++t]=sz;pre=0;
	}
}

void dfs(int x)
{
	if(!x) return;
	dfs(tr[x].se.fi);dfs(tr[x].se.se);
	siz[x]=siz[tr[x].se.fi]+siz[tr[x].se.se]+1;
}

LL qpow(LL x,LL y)
{
	LL ret=1;
	for(;y;y>>=1,x=x*x%mod) if(y&1) ret=ret*x%mod;
	return ret;
}

int main()
{
//	freopen("2653.in","r",stdin);
//	freopen("2653.out","w",stdout);
	
	int T=read(); inv[0]=1; for(int i=1;i<N;++i) inv[i]=qpow(i,mod-2);
	while(T--)
	{
		n=read();init();
		for(int i=1;i<=n;++i) a[i]=read();
		build();dfs(rt);
		LL ans=(LL)n*inv[2]%mod;
		for(int i=1;i<=n;++i) ans=ans*inv[siz[i]]%mod;
		printf("%lld\n",ans);
	}
	
	return 0;
}