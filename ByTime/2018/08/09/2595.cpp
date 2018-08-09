#include <bits/stdc++.h>

using namespace std;

const long long MOD = 100000007;
const int MAXN = 5000001;

long long sum,ans,n;
bool vis[MAXN];
int p[MAXN/4];
int m=0;

void pre()
{
	for (int i=2;i<MAXN;i++)
	{
		if (!vis[i])
			p[m++]=i;
		for (int j=0;j<m && p[j]*i<MAXN;j++)
		{
			vis[p[j]*i]=1;
			if (i%p[j]==0)
				break;
		}
	}
	return ;
}

int main()
{
	freopen("2595.in","r",stdin);
	freopen("2595.out","w",stdout);
	pre();
	while (scanf("%lld",&n)==1 && n!=0)
	{
		ans=1;
		for (int i=0;i<m;i++)
		{
			sum=0;
			for (long long j=p[i];j<=n;j*=p[i])
				(sum+=((n+1)/j-1+1)*((n+1)/j-1)/2*j+((n+1)/j-1+1)*(n-((n+1)/j-1)*j-(j-1)))%=MOD;
			ans=(ans*(sum+1))%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}