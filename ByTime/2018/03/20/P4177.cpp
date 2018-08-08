#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int MAXN = 2509,
		  MAXM = MAXN*MAXN,
		  INF  = 2000000009;

int _next[MAXM*2],_node[MAXM*2],_head[MAXN],_val[MAXM*2],_h[MAXN];
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
	int v,tmp,ans=0;
	if (u==T)
		return Min;
	for (int i=_h[u];~i;i=_next[i],_h[u]=i)
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
	int v,k,a,b;
	ans=0;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	S=0,T=n+m+1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&v,&k);
		ans+=v;
		_connect(S,i,v);
		for (int j=0;j<k;j++)
		{
			scanf("%d%d",&a,&b);
			_connect(i,a+n,b);
		}
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&v);
		_connect(i+n,T,v);
	}
	while (BFS())
	{
		memcpy(_h,_head,sizeof _h);
		ans-=DFS(S,INF);
	}
	printf("%d\n",ans);
	return 0;
}
