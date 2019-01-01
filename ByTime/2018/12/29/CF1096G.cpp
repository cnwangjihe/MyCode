// Date      : 2018-12-25 14:26:24
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/G
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

const int MAXN = 2000009;
const int MOD  = 998244353;

long long f[MAXN],rev[MAXN];
long long prt[2];
int n,m,len;


int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if (k&(1<<i))
			ans=1ll*ans*a%MOD;
	return ans;
}

void init(int n)
{
	int k=0;
	long long t=MOD-1;
	long long p[1000];
	for (int i=2;1ll*i*i<=t;i++)
	{
		if (t%i)
			continue;
		p[k++]=i;
		while (t%i==0)
			t/=i;
	}
	if (t!=1)
		p[k++]=t;
	bool flag;
	for (long long i=1;i<MOD;i++)
	{
		flag=1;
		for (int j=0;j<k && flag;j++)
			if (qpow(i,(MOD-1)/p[j])==1)
				flag=0;
		if (flag)
		{
			prt[1]=i;
			break;
		}
	}
	prt[0]=qpow(prt[1],MOD-2);
//	std::cerr << prt[0] << ' ' << prt[1] << '\n';
	for (len=1;len<=n;len<<=1);
	return ;
}

void ntt_pre()
{
	int l=LOG2(len);
	rev[0]=0;
	for (int i=1;i<len;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	return ;
}

void ntt(long long a[],int n,int type)
{
	for (int i=0;i<n;i++)
		if (i<rev[i])
			std::swap(a[i],a[rev[i]]);
	for (int mid=1;mid<n;mid<<=1)
	{
		long long wn=qpow(prt[type==1],(MOD-1)/(mid<<1));
		for (int i=0;i<n;i+=(mid<<1))
		{
			long long w=1;
			for (int j=i;j<i+mid;j++,w=w*wn%MOD)
			{
				long long x=a[j],y=w*a[j+mid]%MOD;
				a[j]=(x+y)%MOD;
				a[j+mid]=(x-y+MOD)%MOD;
			}
		}
	}
	return ;
}

int main()
{
//	freopen("CF1096G.in","r",stdin);
//	freopen("CF1096G.out","w",stdout);
	int k;
	scanf("%d%d",&n,&k);
	n/=2;
	init(n*10);
	memset(f,0,sizeof f);
	int v;
	for (int i=0;i<k;i++)
	{
		scanf("%d",&v);
		f[v]=1;
	}
	ntt_pre();
	ntt(f,len,1);
	for (int i=0;i<=len;i++)
		f[i]=qpow(f[i],n);
	ntt(f,len,-1);
	int inv=qpow(len,MOD-2);
	int ans=0;
	for (int i=0;i<=n*10;i++)
		(ans+=qpow(f[i]*inv%MOD,2))%=MOD;
	printf("%d\n",ans);
	return 0;
}