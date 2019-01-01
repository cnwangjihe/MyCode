// Date      : 2018-12-28 23:54:41
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/F
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 200009,
		  MOD  = 998244353;


int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if (k&(1<<i))
			ans=1ll*ans*a%MOD;
	return ans;
}

struct Tree
{
	int v[MAXN];
	inline void clear() {memset(v,0,sizeof v);}
	Tree() {clear();}
	void inc(int x)
	{
		for (;x<MAXN;x+=x&-x)
			v[x]++;
	}
	int sum(int x)
	{
		int sum=0;
		for (;x;x-=x&-x)
			sum+=v[x];
		return sum;
	}
}T;

int a[MAXN];
int n,ans=0,cnt1=0,cnt2=0;

int main()
{
//	freopen("CF1096F.in","r",stdin);
//	freopen("CF1096F.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]==-1)
			cnt1++;
	}
	for (int i=0;i<n;i++)
		if (a[i]!=-1)
		{
			(ans+=(T.sum(n)-T.sum(a[i]))%MOD)%=MOD;
			T.inc(a[i]);
		}
	int tmp;
	int inv=qpow(cnt1,MOD-2);
	for (int i=0;i<n;i++)
	{
		if (a[i]==-1)
		{
			cnt2++;
			continue;
		}
		tmp=(1ll*n-a[i]-T.sum(n)+T.sum(a[i]))%MOD;
		(ans+=1ll*(cnt1-tmp)*(cnt1-cnt2)%MOD*inv%MOD)%=MOD;
		(ans+=1ll*tmp*cnt2%MOD*inv%MOD)%=MOD;
	}
	(ans+=1ll*cnt1*(cnt1-1)%MOD*qpow(4,MOD-2)%MOD)%=MOD;
	printf("%d\n",(ans+MOD)%MOD);
	return 0;
}