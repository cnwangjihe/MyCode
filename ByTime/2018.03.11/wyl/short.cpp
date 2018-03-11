#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 600009;

int fa[MAXN];
int _head[MAXN],_node[MAXM*2],_next[MAXM*2];
int fp=0,n,m,k;
int line[MAXN],dis[MAXN],vis[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int find(int u)
{
	int t=u,tmp;
	while (fa[u]!=u)
		u=fa[u];
	while (fa[t]!=t)
	{
		tmp=fa[t];
		fa[t]=u;
		t=tmp;
	}
	return u;
}

int solve(int x,int y,int k)
{
	if(find(x) != find(y))
		return -1;
	int u,v,head=0,tail=0;
	vis[x]=k,vis[y]=-k;
	line[tail++]=x;
	line[tail++]=y;
	dis[x]=dis[y]=0;
	while (head!=tail)
	{
		u=line[head++];
		for(int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (vis[v] == vis[u])
				continue;
			if (vis[v] == -vis[u])
				return dis[u]+dis[v]+1;
			vis[v]=vis[u];
			dis[v]=dis[u]+1;
			line[tail++]=v;
		}
	}
	return -1;
}
int main()
{
	freopen("short.in","r",stdin);
	freopen("short.out","w",stdout);
	int x,y;
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y),_connect(y,x);
		fa[find(x)] = find(y);
	}
	for (int i=1;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",solve(x,y,i));
	}
	return 0;
}