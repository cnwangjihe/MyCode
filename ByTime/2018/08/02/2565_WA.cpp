#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000,
		  INF  = 10009;

int _head[MAXN],_node[MAXN*2],_next[MAXN*2];
long long ans=0;
int a[MAXN];
int n,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa,int Max,int Min,int d)
{
	int v;
	d++;
	Max=max(Max,a[u]);
	Min=min(Min,a[u]);
	ans+=(long long)(Max-Min)*(long long)d;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u,Max,Min,d);
	}
	return ;
}

int main()
{
	freopen("2565.in","r",stdin);
	freopen("2565.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
	}
	for (int i=1;i<=n;i++)
		dfs(i,0,-1,INF,0);
	printf("%lld\n",ans/2ll);
	return 0;
}