// Date      : 2019-03-01 09:23:05
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXV = 10000009,
		  MAXM = 309,
		  MOD  = 1000000007;

struct SegmentTree
{
	int t[MAXN*4];
	inline void Up(int u) {t[u]=t[u*2]+t[u*2+1];}
	void Add(int u,int l,int r,int p,int v)
	{
		if (l==r)
		{
			t[u]+=v;
			return ;
		}
		int mid=(l+r)>>1;
		if (p<=mid)
			Add(u*2,l,mid,p,v);
		else
			Add(u*2+1,mid+1,r,p,v);
		Up(u);
	}
	int Query(int u,int l,int r,int al,int ar)
	{
		if (al>ar)
			return 0;
		if (al<=l && ar>=r)
			return t[u];
		int mid=(l+r)>>1,ans=0;
		if (al<=mid)
			ans+=Query(u*2,l,mid,al,ar);
		if (ar>mid)
			ans+=Query(u*2+1,mid+1,r,al,ar);
		ans=ans>MOD?ans-MOD:ans;
		return ans;
	}
};

SegmentTree ST;
int fac[MAXV],fav[MAXV];
int a[MAXM],b[MAXN];
int n,m,k,Max,Sum,ans=0;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

inline int C(int n,int m)
{
	if (m<0)
		return 1;
	return (m>n)?0:1ll*fac[n]*fav[n-m]%MOD*fav[m]%MOD;
}

void init()
{
	fac[0]=fav[0]=1;
	for (int i=1;i<MAXV;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXV-1]=qpow(fac[MAXV-1],MOD-2);
	for (int i=MAXV-2;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	return ;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	init();
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<m;i++)
		scanf("%d",&a[i]),Sum+=a[i];
	Max=a[0];
	for (int i=0;i<=a[0];i++)
		ST.Add(1,0,Sum,i,1);
	for (int i=1;i<m;i++)
	{
		for (int j=1;j<=Max;j++)
			b[j]=ST.Query(1,0,Sum,j-a[i],j-1);
		for (int j=Max+1;j<=Max+a[i];j++)
			b[j]=ST.Query(1,0,Sum,j-a[i],Max);
		for (int j=1;j<=Max+a[i];j++)
			ST.Add(1,0,Sum,j,b[j]);
		Max+=a[i];
		if (Max>k)
			Max=k;
	}
	for (int i=0;i<=Sum;i++)
		(ans+=1ll*ST.Query(1,0,Sum,i,i)*C(k-i+n-m-1,n-m-1)%MOD)%=MOD;
	printf("%d\n",ans);
	return 0;
}