#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 5009+50009,
		  MAXM = 50000*4,
		  INF  = 1000000009;

int _next[MAXM*2],_node[MAXM*2],_head[MAXN],_val[MAXM*2];
bool vis[MAXN];
int line[MAXN],dis[MAXN];
int fp=0,S,T,n,m,ans=0;

void _add(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v)
{
	_add(a,b,v);
	_add(b,a,0);
	return ;
}

bool BFS()
{
	int head=0,tail=0,u,v;
	memset(vis,0,sizeof vis);
	line[tail++]=S;
	vis[S]=1;
	dis[S]=1;
	while (head!=tail)
	{
		u=line[head++];
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (vis[v] || !_val[i])
				continue;
			vis[v]=1;
			dis[v]=dis[u]+1;
			line[tail++]=v;
		}
	}
	return vis[T];
}

int DFS(int u,int Min)
{
//  cerr << u <<endl;
	int v,tmp,ans=0;
	if (u==T)
		return Min;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (!_val[i] || dis[v]!=dis[u]+1)
			continue;
		tmp=DFS(v,min(Min,_val[i]));
		_val[i]-=tmp;
		_val[i^1]+=tmp;
		ans+=tmp;
		Min-=tmp;
		if (!Min)
			return ans;
	}
	return ans;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int a,b,v;
	scanf("%d%d",&n,&m);
	S=0,T=n+m+1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&v);
		_connect(S,i,v);
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&v);
		_connect(a,i+n,INF);
		_connect(b,i+n,INF);
		_connect(i+n,T,v);
		ans+=v;
	}
	while (BFS())
		ans-=DFS(S,INF);
	printf("%d\n",ans);
	return 0;
}