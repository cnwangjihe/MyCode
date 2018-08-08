#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*2;

int _head[MAXN],_next[MAXM],_node[MAXM];
int val[MAXN];
int ans=0,n,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa,int cnt,int sum)
{
	sum+=val[u];
	cnt+=(val[u]==1);
	if (sum<0)
		return ;
	if (sum==0)
		ans=max(ans,cnt);
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u,cnt,sum);
	}
	return ;
}

int main()
{
	freopen("2443.in","r",stdin);
	freopen("2443.out","w",stdout);
	int a;
	while (scanf("%d",&n)==1)
	{
		ans=fp=0;
		memset(_head,-1,sizeof _head);
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&val[i]);
			if (a)
				_connect(a,i),_connect(i,a);
		}
		for (int i=1;i<=n;i++)
			dfs(i,0,0,0);
		printf("%d\n",ans);
	}
}