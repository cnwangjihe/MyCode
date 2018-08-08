#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 100009;
const long long INF = 100000000000009ll;

int n,x,y,root,fp=0;
long long v;
long long val[MAXN*2];
int _next[MAXN*2],head[MAXN],node[MAXN*2];
bool vis[MAXN];

void _connect(int x,int y,long long v)
{
	_next[fp]=head[x];
	node[fp]=y;
	val[fp]=v;
	head[x]=fp++;
	return ;
}

long long dfs(int u,long long v)
{
	vis[u]=1;
	long long cost=0ll;
	bool f=0;
	for (int i=head[u];~i;i=_next[i])
		if (!vis[node[i]])
			cost+=dfs(node[i],val[i]),f=1;
	return f?min(v,cost):v;
}

int main()
{
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&root);
	for (int i=0;i<n-1;i++)
	{
		scanf("%d%d%d",&x,&y,&v);
		_connect(x,y,v);
		_connect(y,x,v);
	}
	printf("%lld",dfs(root,INF));
	return 0;
}
