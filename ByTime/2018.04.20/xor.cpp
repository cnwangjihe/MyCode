#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 50009;

int n,m,q,fp=0,ans;
int way[MAXN];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2],_val[MAXN*2];

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		way[v]=way[u]^_val[i];
		dfs(v,u);
	}
}

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int x,y,v;
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&v);
		_connect(x,y,v);
		_connect(y,x,v);
	}
	dfs(1,1);
	for (int i=1;i<=q;i++)
	{
		ans=0;
		scanf("%d%d",&x,&y);
		for (int i=x;i<=y;i++)
			for (int j=x;j<=y;j++)
			if (i!=j && (way[i]^way[j])>m)
				ans++;
		printf("%d\n",ans/2);	
	}
	
	return 0;
}
