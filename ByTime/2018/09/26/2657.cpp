#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  lim  = 333,
		  MOD  = 1000000007;

struct Tquery{int l,r,i,g;};

Tquery q[MAXN];
int fac[MAXN],fav[MAXN],ans[MAXN];
int n;

inline bool _cmp(Tquery a,Tquery b) {return (a.g==b.g)?a.r<b.r:a.l<b.l;}
inline int C(int n,int m) {return (n<m)?0:1ll*fac[n]*fav[m]%MOD*fav[n-m]%MOD;}

int qpow(int a,int b)
{
	int ans=1;
	for (int i=0;(1<<i)<=b;i++,a=1ll*a*a%MOD)
		if ((1<<i)&b)
			ans=1ll*ans*a%MOD;
	return ans;
}

int main()
{
	freopen("2657.in","r",stdin);
	freopen("2657.out","w",stdout);

	fac[0]=fac[1]=1;fav[0]=fav[1]=1;
	for (int i=2;i<MAXN;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
	for (int i=MAXN-2;i>1;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&q[i].r,&q[i].l);
		q[i].i=i,q[i].g=(q[i].l-1)/lim+1;
	}
	sort(q+1,q+n+1,_cmp);
	int l=1,r=1,t=2;
	for (int i=1;i<=n;i++)
	{
		while(l<q[i].l)
			(t+=C(r,++l))%=MOD;
		while(l>q[i].l)
			(t+=MOD-C(r,l--))%=MOD;
		while(r<q[i].r)
			t=2ll*t%MOD,(t+=MOD-C(r++,l))%=MOD;
		while(r>q[i].r)
			(t+=C(--r,l))%=MOD,t=1ll*t*fav[2]%MOD;
		ans[q[i].i]=t;
	}
	for (int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;	
}