#include <bits/stdc++.h>

using namespace std;

int ans=0;
bool vis[100];
int v[100];
int n;

void dfs(int c,int k)
{
	if (c>k)
	{
		ans++;
		return ;
	}
	for (int i=1;i<=k;i++)
	{
		if (vis[i] || (c>1 && i<v[c/2]))
			continue;
		v[c]=i;
		vis[i]=1;
		dfs(c+1,k);
		vis[i]=0;
	}
	return ;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		ans=0;
		dfs(1,i);
		printf("%d: %d\n",i,ans);
	}
	return 0;
}