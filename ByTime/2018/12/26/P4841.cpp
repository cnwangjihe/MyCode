// Date      : 2018-12-26 15:40:19
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::
using std::cerr;
using std::swap;
using std::fill;
using std::copy;

const int MOD  = 479*(1<<21)+1,
		  MAXN = 130009;

const int prt[2]={334845270,3};
int Wn[2][23];
int a[MAXN*8],b[MAXN*8],rb[MAXN*8],tmp[MAXN*8];
int fac[MAXN],fav[MAXN];
int n;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1ll<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

void init()
{
	int t=MOD-1;
	for (int i=0;i<=21;i++)
	{
		Wn[0][i]=qpow(prt[0],t/(1<<i));
		Wn[1][i]=qpow(prt[1],t/(1<<i));
	}
	fac[0]=fav[0]=1;
	for (int i=1;i<MAXN;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	fav[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
	for (int i=MAXN-2;i;i--)
		fav[i]=1ll*fav[i+1]*(i+1)%MOD;
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

void polynomial_inverse(int n,int *a,int *b,int *c)
{
	if (n==1)
	{
		b[0]=qpow(a[0],MOD-2);
		return ;
	}
	polynomial_inverse((n+1)>>1,a,b,c);
	int len=1;
	while (len<2*n)
		len<<=1;
	copy(a,a+n,c);
	fill(c+n,c+len,0);
	ntt(len,c,1);
	ntt(len,b,1);
	for (int i=0;i<len;i++)
		b[i]=((2ll-1ll*c[i]*b[i])%MOD+MOD)*b[i]%MOD;
	ntt(len,b,-1);
	int inv=qpow(len,MOD-2);
	for (int i=0;i<n;i++)
		b[i]=1ll*b[i]*inv%MOD;
	fill(b+n,b+len,0);
}

int main()
{
//	freopen("P4841.in","r",stdin);
//	freopen("P4841.out","w",stdout);
	init();
	scanf("%d",&n);
	for (int i=0;i<=n;i++)
	{
		b[i]=1ll*qpow(2,(1ll*i*(i-1)/2ll%(MOD-1)))*fav[i]%MOD;
		if (i>0)
			a[i]=1ll*qpow(2,(1ll*i*(i-1)/2ll%(MOD-1)))*fav[i-1]%MOD;
	}
	polynomial_inverse(n+1,b,rb,tmp);
	int len=1;
	while (len<=(n<<1))
		len<<=1;
	ntt(len,a,1);
	ntt(len,rb,1);
	for (int i=0;i<len;i++)
		a[i]=1ll*a[i]*rb[i]%MOD;
	ntt(len,a,-1);
	int inv=qpow(len,MOD-2);
	printf("%lld\n",1ll*a[n]*fac[n-1]%MOD*1ll*inv%MOD);
	return 0;
}