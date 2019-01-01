// Date      : 2018-12-28 16:22:32
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MOD  = 998244353,
		  MAXC = 100009;

int prt[2];
int n,c,m,len;
int a[MAXC*2],b[MAXC*2],f[MAXC*2];
int fac[MAXC],fav[MAXC];
int Wn[2][30];

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if (k&(1<<i))
			ans=1ll*ans*a%MOD;
	return ans;
}

void init(int n,int m)
{
	prt[1]=3;
	fac[0]=fav[0]=1;
	for (int i=1;i<MAXC;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXC-1]=qpow(fac[MAXC-1],MOD-2);
	for (int i=MAXC-2;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
	prt[0]=qpow(prt[1],MOD-2);
//	std::cerr << prt[0] << ' ' << prt[1] << '\n';
	for (len=1;len<=n+m;len<<=1);
	return ;
}

void ntt(int n,int *a,int type)
{
	for (int i=0,j=0;i<n;i++)
	{
		if (i>j)
			swap(a[i],a[j]);
		for (int l=(n>>1);(j^=l)<l;l>>=1);
	}
	int wn,w,x,y;
	for (int mid=1,midt=0;mid<n;mid<<=1,midt++)
	{
		wn=Wn[type==1][midt+1];
		for (int i=0;i<n;i+=(mid<<1))
		{
			w=1;
			for (int j=i;j<i+mid;j++,w=1ll*w*wn%MOD)
			{
				x=a[j],y=1ll*a[j+mid]*w%MOD;
				a[j]=(x+y)%MOD,a[j+mid]=(x-y+MOD)%MOD;
			}
		}
	}
	return ;
}

int main()
{
//	freopen("chocolate.in","r",stdin);
//	freopen("chocolate.out","w",stdout);
	scanf("%d%d%d",&n,&c,&m);
	init(n,n);
	for (int i=1;i<=n;i+=2)
		a[i]=fav[i];
	for (int i=0;i<=n;i+=2)
		b[i]=fav[i];
	ntt(len,a,1);
	ntt(len,b,1);
	for (int i=0;i<len;i++)
		f[i]=1ll*qpow(a[i],m)*qpow(b[i],c-m)%MOD;
	ntt(len,f,-1);
	cerr << 1ll*f[n]*qpow(qpow(c,n),MOD-2)%MOD;
	return 0;
}