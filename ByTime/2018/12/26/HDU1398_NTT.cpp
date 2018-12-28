// Date      : 2018-12-26 08:59:15
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 生成函数+NTT
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

const int MAXN = 309*100;
const long long MOD = 998244353;
long long a[MAXN],f[MAXN];
int rev[MAXN];
long long prt[2];
int n,inv,len;

long long qpow(long long a,int k)
{
	long long ans=1;
	for (int i=0;(1<<i)<=k;i++,a=a*a%MOD)
		if (k&(1<<i))
			ans=ans*a%MOD;
	return ans;
}

int init(int n,int m)
{
	int cnt=0;
	long long t=MOD-1;
	int p[1009];
	for (int i=2;i*i<=t;i++)
	{
		if (t%i)
			continue;
		p[cnt++]=i;
		while (t%i==0)
			t/=i;
	}
	if (t!=1)
		p[cnt++]=t;
	bool flag;
	for (int i=1;i<MOD;i++)
	{
		flag=1;
		for (int j=0;j<cnt && flag;j++)
			if (qpow(i,(MOD-1)/p[j])==1)
				flag=0;
		if (flag)
		{
			prt[1]=i;
			break;
		}
	}
	prt[0]=qpow(prt[1],MOD-2);
	int len=1;
	while (len<=n+m)
		len<<=1;
	int l=LOG2(len);
	for (int i=1;i<len;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	return len;
}

void ntt(long long a[],int n,int type)
{
	for (int i=0;i<n;i++)
		if (rev[i]>i)
			std::swap(a[rev[i]],a[i]);
	for (int mid=1;mid<n;mid<<=1)
	{
		long long wn=qpow(prt[type==1],(MOD-1)/(mid<<1));
		for (int i=0;i<n;i+=(mid<<1))
		{
			long long w=1;
			for (int j=i;j<i+mid;j++,w=w*wn%MOD)
			{
				long long x=a[j],y=a[j+mid]*w%MOD;
				a[j]=(x+y)%MOD,a[j+mid]=(x-y+MOD)%MOD;
			}
		}
	}
	return ;
}

int main()
{
//	freopen("HDU1398.in","r",stdin);
//	freopen("HDU1398.out","w",stdout);
	memset(f,0,sizeof f);
	f[0]=1;
	len=init(300,300);
	inv=qpow(len,MOD-2);
	for (int i=1;i<=17;i++)
	{
		memset(a,0,sizeof a);
		for (int j=0;j<=300;j+=i*i)
			a[j]=1;
		ntt(f,len,1);
		ntt(a,len,1);
		for (int j=0;j<=len;j++)
			f[j]=f[j]*a[j]%MOD;
		ntt(f,len,-1);
		for (int j=0;j<=300;j++)
			f[j]=f[j]*inv%MOD;
		for (int j=301;j<len;j++)
			f[j]=0;
	}
	while (scanf("%d",&n)==1 && n)
		printf("%lld\n",f[n]);
	return 0;
}