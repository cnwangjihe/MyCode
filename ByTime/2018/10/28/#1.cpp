#include <bits/stdc++.h>

using namespace std;

int c[42];
int n,m,k;

void count(int route)
{
	int cnt=0;
	for (;route;route^=(route&(-route)))
		cnt++;
	c[cnt]++;
}

void dfs(int step,int route)
{
	if (step==(n+m)/2)
	{
		count(route);
		return ;
	}
	dfs(step+1,(route<<1)+0);
	dfs(step+1,(route<<1)+1);
	return ;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
/*	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i]);
*/
	dfs(0,0);
	for (int i=0;i<=n+m/2;i++)
		cerr << c[i] << '\n';
	return 0;
}