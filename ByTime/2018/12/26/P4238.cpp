// Date      : 2018-12-26 10:16:20
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : NTT,多项式求逆
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use 
using std::cerr;
using std::swap;
using std::fill;
using std::copy;

const int MOD  = (1<<23)*119+1,
		  MAXN = 400009;

const int prt[2]={332748118,3};
int a[MAXN],b[MAXN],c[MAXN];
int Wn[2][25];
int n;

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
	int t=MOD-1;
	for (int i=0;i<=23;i++)
	{
		Wn[0][i]=qpow(prt[0],t/(1<<i));
		Wn[1][i]=qpow(prt[1],t/(1<<i));
	}
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
//	freopen("P4238.in","r",stdin);
//	freopen("P4238.out","w",stdout);
	init();
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);

	polynomial_inverse(n,a,b,c);
	for (int i=0;i<n;i++)
		printf("%d ",b[i]);
	putchar('\n');
	return 0;
}