#include <bits/stdc++.h>

using namespace std;

const int MAXN = 12;

bool vis[MAXN];
int a[MAXN];
int n,m,ans;

void dfs(int k)
{
	if (k>n)
	{
		int cnt=0;
		cnt+=(a[1]==n || a[1]==1 || a[1]==2);
		cnt+=(a[n]==1 || a[n]==n || a[n]==n-1);
		for (int i=2;i<n;i++)
			if (a[i]>=i-1 && a[i]<=i+1)
				cnt++;
		if (cnt>=m) 
			ans++;
		return ;
	}
	for (int i=1;i<=n;i++)
		if (!vis[i])
		{
			vis[i]=1;
			a[k]=i;
			dfs(k+1);
			vis[i]=0;
		}
	return ;
}

int main()
{
	freopen("2648.in","r",stdin);
	freopen("2648.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		scanf("%d%d",&n,&m);
		dfs(1);
		printf("Case %d: %d\n",cn,ans);
	}
	return 0;
}