#include <bits/stdc++.h>

using namespace std;

const int MAXN = 45;

long long g[MAXN],ss[MAXN];
long long k;
int h[MAXN];
long long ans[MAXN];
int n;

long long dfs(int u,long long sum)
{
	if (sum>=k)
	{
		if (ans[u]==-1)
		{
			ans[u]=1;
			for (int i=u+1;i<=n;i++)
				if (h[i]>=h[u])
					ans[u]+=dfs(i,sum+g[i]);
		}
		return ans[u];
	}
	long long sans=0;
	for (int i=u+1;i<=n;i++)
		if (h[i]>=h[u] && ss[i]+sum>=k)
			sans+=dfs(i,sum+g[i]);
	return sans;
}

int main()
{
	freopen("2639.in","r",stdin);
	freopen("2639.out","w",stdout);
	memset(ans,-1,sizeof ans);
	scanf("%d%lld",&n,&k);
	for (int i=1;i<=n;i++)
		scanf("%d%lld",&h[i],&g[i]);
	for (int i=n;i;i--)
		ss[i]=ss[i+1]+g[i];
	printf("%lld\n",dfs(0,0));
	return 0;
}