#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int MAXN = 12009,
		  MAXM = 10009*209,
		  INF  = 1000000009;

int _next[MAXM*2],_node[MAXM*2],_head[MAXN],_val[MAXM*2],_h[MAXN];
bool vis[MAXN];
int line[MAXN],dis[MAXN];
int s[10006];
int fp=0,S,T;

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
	int ans=0,n,m,g,a,b,v,k;
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d",&n,&m,&g);
	S=0,T=n+m+1;
	for (int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&v);
		if (s[i])
			_connect(i,T,v);
		else
			_connect(S,i,v);
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&v,&k);
		ans+=v;
		for (int j=0;j<k;j++)
			scanf("%d",&s[j]);
		scanf("%d",&b);
	//	cerr << b << endl;
		if (a)
		{
			_connect(i+n,T,(b?g:0)+v);
			for (int j=0;j<k;j++)
				_connect(s[j],i+n,INF);
		}
		else
		{
			_connect(S,i+n,(b?g:0)+v);
			for (int j=0;j<k;j++)
				_connect(i+n,s[j],INF);
		}
	}
//	printf("%d\n",ans);
	while (BFS())
	{
		memcpy(_h,_head,sizeof _h);
		ans-=DFS(S,INF);
	}
	printf("%d\n",ans);
	return 0;
}
