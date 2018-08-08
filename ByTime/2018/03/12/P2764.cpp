#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 300,
		  MAXM = 6009*4,
		  INF  = 10000009;

int _next[MAXM*2],_node[MAXM*2],_head[MAXN],_val[MAXM*2];
bool vis[MAXN];
int line[MAXN],dis[MAXN];
int fa[MAXN];
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
//	for (int i=1;i<=2*n+1;i++)
//		cerr << dis[i] << ' ';
//	cerr << '\n';
	return vis[T];
}

int DFS(int u,int Min)
{
//	cerr << u <<endl;
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

int _find(int u)
{
	while (u!=fa[u])
		u=fa[u];
	return u;
}

void _out(int u)
{
	printf("%d ",u);
	for(int i=_head[u];~i;i=_next[i])
		if (_val[i]==0 && _node[i]>n)
			_out(_node[i]-n);
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int a,b;
	scanf("%d%d",&n,&m);
	S=0,T=n*2+1;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,n+b,1);
	}
	for (int i=1;i<=n;i++)
		_connect(S,i,1),
		_connect(i+n,T,1);
	while (BFS())
	{
		ans+=DFS(S,INF);
	//	return 0;
	}
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int u=1;u<=n;u++)
	{
		for (int i=_head[u];~i;i=_next[i])
			if (_node[i]>n && _node[i]<T && _val[i]==0)
				fa[_find(_node[i]-n)]=_find(u);
	}
	for(int i=1;i<=n;i++)
		if(_find(i)==i)
			_out(i),putchar('\n');
	printf("%d\n",n-ans);
	return 0;
}