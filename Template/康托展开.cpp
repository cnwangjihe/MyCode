#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

long long fac[MAXN];
bool vis[MAXN];
int a[MAXN];
int n;

void init(int n)
{
	fac[0]=1;
	for (int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i;
	return ;
}

long long GetRank(int* a,int n)
{
	int c;
	long long ans=0;
	memset(vis,0,sizeof vis);
	for (int i=1;i<=n;i++)
	{
		c=a[i]-1;
		for (int j=1;j<a[i];j++)
			if (vis[j])
				c--;
		vis[a[i]]=1;
		ans+=c*fac[n-i];
	}
	return ans;
}

void GetArray(int* a,int n,long long m)
{
	memset(vis,0,sizeof vis);
	int j,t;
	for (int i=1;i<=n;i++)
	{
		t=m/fac[n-i];
		for (j=1;j<=n;j++)
			if (!vis[j])
			{
				if (t == 0)
					break;
				t--;
			}
		a[i]=j;
		vis[j] = 1;
		m %= fac[n-i];
	}
}
int main()
{
	scanf("%d",&n);
	init(n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	printf("%lld\n",GetRank(a,n)+1);
	GetArray(a,n,GetRank(a,n));
	for (int i=1;i<=n;i++)
		printf("%d ",a[i]);
	return 0;
}