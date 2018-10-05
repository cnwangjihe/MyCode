#include <bits/stdc++.h>

using namespace std;

const int MAXN = 59;

int a[MAXN];
bool vis[MAXN];
int ans[MAXN*MAXN];
int n,p;

void dfs(int k)
{
	if (k>n)
	{
		int sum=0;
		for (int i=1;i<=n;i++)
			sum+=abs(a[i]-i);
		ans[sum]++;
		ans[sum]%=p;
		return ;
	}
	for (int i=1;i<=n;i++)
	{
		if (vis[i])
			continue;
		a[k]=i;
		vis[i]=1;
		dfs(k+1);
		vis[i]=0;
	}
	return ;
}

int main()
{
	freopen("2669.in","r",stdin);
	freopen("2669.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		memset(ans,0,sizeof ans);
		scanf("%d%d",&n,&p);
		dfs(1);
		for (int i=0;i<n*n;i++)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}