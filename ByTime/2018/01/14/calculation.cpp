#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

struct Tnode {long long sum[2],k,b;};

const int MAXN = 100009;
const long long MOD  = 1000000007ll;
		  
Tnode t[MAXN*4];
int n,q;
int l,r,k,b;
int a[MAXN];
long long s[MAXN];
char c;

inline void _add(int u,long long k,long long b,int len)
{
	t[u].k+=k;
	t[u].b+=b;
	t[u].sum[1]+=((s[len-1]*((k*k)%MOD))%MOD);
	t[u].sum[1]%=MOD;
	t[u].sum[1]+=((((b*b)%MOD)*len)%MOD);
	t[u].sum[1]%=MOD;
	t[u].sum[1]+=(((((len-1ll)*len)%MOD)*b)%MOD);
	t[u].sum[1]%=MOD;
	t[u].sum[1]+=((2ll*t[u].sum[0]*b)%MOD);
	t[u].sum[1]%=MOD;
	t[u].sum[1]+=(((long long)t[u].sum[0]*(len+1)/2ll-(t[u].sum[0]))%MOD);
	t[u].sum[1]%=MOD;
	t[u].sum[0]+=((b*len+((((len-1)*len/2)%MOD)*k)%MOD)%MOD);
	t[u].sum[0]%=MOD;
//	t[u].sum
	return ;
}

inline void _down(int u,int tmp,int t2)
{
	_add(u*2,t[u].k,t[u].b,tmp);
	_add(u*2+1,t[u].k,((long long)t[u].b+(long long)tmp*t[u].k)%MOD,t2+1-tmp);
//	t[u*2].k+=t[u].k;
//	t[u*2+1].k+=t[u].k;
//	t[u*2].b+=t[u].b;
//	t[u*2+1].b+=(t[u].b+(tmp*k)%MOD)%MOD;
//	t[u*2].k%=MOD,t[u*2+1].k%=MOD,
//	t[u*2].b%=MOD,t[u*2+1].b%=MOD;
//	t[u*2].sum[0]+=(((2ll*t[u].b+(tmp-1)*(long long)t[u].k)*(long long)tmp/2ll)%(long long)MOD);
//	t[u*2+1].sum[0]+=(((2ll*t[u].b+tmp*(long long)t[u].k+t2*(long long)t[u].k)*(long long)((long long)t2+1-tmp))%(long long)MOD);
//	t[u*2].sum[0]%=MOD,t[u*2+1].sum[0]%=MOD;
	
//	t[u*2]+=t[u]
	
	t[u].b=t[u].k=0ll;
	return ;
}

inline void _up(int u)
{
	t[u].sum[0]=t[u*2].sum[0]+t[u*2+1].sum[0];
	t[u].sum[1]=t[u*2].sum[1]+t[u*2+1].sum[1];
	t[u].sum[0]%=MOD,t[u].sum[1]%=MOD;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].sum[0]=a[l];
		t[u].sum[1]=((long long)a[l]*a[l])%MOD;
		t[u].k=0;
		t[u].b=0;
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	_up(u);
}

void _update(int u,int l,int r,int al,int ar,int k,int b)
{
	if (al<=l && ar>=r)
	{
		_add(u,k,b,r-l+1);
		return ;
	}
	int mid=(l+r)/2;
	_down(u,mid-l+1,r-l);
	if (al<=mid) _update(u*2,l,mid,al,ar,k,b);
	if (ar>mid) _update(u*2+1,mid+1,r,al,ar,k,b+k*(mid-l+1));
	_up(u);
	return ;
}

long long _ask(int u,int l,int r,int al,int ar,bool type)
{
	if (al<=l && ar>=r)
		return t[u].sum[type];
	int mid=(l+r)/2;
	long long ans=0;
	_down(u,mid-l+1,r-l);
	if (al<=mid) ans+=_ask(u*2,l,mid,al,ar,type);
	if (ar>mid) ans+=_ask(u*2+1,mid+1,r,al,ar,type);
	return ans%MOD;
}

int main()
{
	freopen("calculation.in","r",stdin);
	freopen("calculation.out","w",stdout);
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	s[0]=0ll;
	for (int i=1;i<=n;i++)
		s[i]=s[i-1]+((long long)i*i)%MOD,s[i]%=MOD;
	_build(1,1,n);
	for (int i=0;i<q;i++)
	{
		do {c=getchar();}
			while (c<'A' || c>'C');
		if (c=='A')
		{
			scanf("%d%d%d%d",&l,&r,&k,&b);
			_update(1,1,n,l,r,k,b);
		}
		else
		{
			scanf("%d%d",&l,&r);
			printf("%I64d\n",_ask(1,1,n,l,r,(c=='C')));
			
		}
	}
	return 0;
}
