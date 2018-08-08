#include <fstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

struct edge
{
	int to,next;
}q[10000];
int fp,n;
int v[10000],h[10000],f[10000],g[10000],fa[10000],cnt[10000];
void _add(int x,int y)
{
	fp++;
	q[fp].next=h[x];
	q[fp].to=y;
	h[x]=fp;
}
void dfs(int x)
{
	int y;
	f[x]=v[x];
	for (int i=h[x];i!=0;i=q[i].next)
	{
		y=q[i].to;
		fa[y]=x;
		dfs(y);
		f[x]+=g[y];
		g[x]+=max(g[y],f[y]);
	}
}
int main()
{
	scanf("%d",&n);
	int x,y,k;
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	for (int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&x,&y);
		cnt[x]++;
		_add(y,x);
	}
	for (int i=1;i<=n;i++)
		if (!cnt[i])
		{
			k=i;
			break;
		}
	dfs(k);
	printf("%d\n",max(f[k],g[k]));
	return 0;
}
