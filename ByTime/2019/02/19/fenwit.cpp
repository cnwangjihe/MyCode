// Date      : 2019-02-19 09:21:31
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : FWT
// Notice    : None

#include <bits/stdc++.h>

#define Count(x) __builtin_popcount(x)

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXM = 19,
		  MAXN = (1<<MAXM);
typedef const long long cll;

long long MOD,INV2;
int n,m,t;
long long f[MAXN],c[MAXN],b[MAXM];
long long g[2][MAXN];
int cnt[MAXN];

inline long long Mul(cll& x,cll& y,cll& MOD)
{
	long long tmp=(x*y-(long long)((long double)x*y/MOD+0.5)*MOD);
	return tmp<0?tmp+MOD:tmp;
}

inline long long Mod(long long a,cll& MOD)
{
	while (a>MOD)
		a-=MOD;
	while (a<0)
		a+=MOD;
	return a;
}
long long Read(cll& MOD)
{
	long long x=0;int c=getchar();
	while (c<'0' || c>'9')
		c=getchar();
	while (c>='0' && c<='9')
		x=Mod(Mul(x,10ll,MOD)-'0'+c,MOD),c=getchar();
	return x;
}

long long qpow(long long a,cll& k,cll& MOD)
{
	long long ans=1;
	for (long long i=0;(1ll<<i)<=k;a=Mul(a,a,MOD),i++)
		if (k&(1ll<<i))
			ans=Mul(ans,a,MOD);
	return ans;
}

void fwt(long long a[],int n,cll& MOD)
{
	for (int d=1;d<n;d<<=1)
		for (int m=d<<1,i=0;i<n;i+=m)
			for (int j=0;j<d;j++)
			{
				long long x=a[i+j],y=a[i+j+d];
				a[i+j]=Mod(x+y,MOD);
				a[i+j+d]=Mod(x-y,MOD);
			}
	return ;
}

long long GetPhi(long long x)
{
	long long ans=x;
	for (long long i=2;i<=x;i++)
	{
		if (x%i==0)
			ans=ans*(i-1)/i;
		for (;x%i==0;x/=i);
	}
	if (x!=1)
		ans=ans*(x-1)/x;
	return ans;
}

int main()
{
	freopen("fenwit.in","r",stdin);
	freopen("fenwit.out","w",stdout);
	scanf("%d%lld",&m,&MOD);
	t=Read(GetPhi(MOD));
	n=(1<<m);
	for (int i=0;i<n;i++)
		f[i]=Read(MOD);
	for (int i=0;i<m+2;i++)
		b[i]=Read(MOD);
	for (int i=0;i<n;i++)
		c[i]=b[Count(i)];
	MOD<<=m;
	fwt(f,n,MOD);
	fwt(c,n,MOD);
	for (int i=0;i<n;i++)
		f[i]=Mul(f[i],qpow(c[i],t,MOD),MOD);
	fwt(f,n,MOD);
	for (int i=0;i<n;i++)
		printf("%lld\n",f[i]>>m);
	return 0;
}