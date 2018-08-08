#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 34,
		  MAXM = 1009;
const long long INF  = 100000000000009ll;

int _next[MAXM*2],_node[MAXM*2],_head[MAXN];
long long _val[MAXM*2];
bool vis[MAXN];
int line[MAXN],dis[MAXN];
int fp=0,S,T,n,m;
long long ans=0;

void _add(int a,int b,long long v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,long long v)
{
	_add(a,b,v);
	_add(b,a,0ll);
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

long long DFS(int u,long long Min)
{
//  cerr << u <<endl;
	int v;
	long long tmp,ans=0;
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
	scanf("%d%d",&n,&m);
	S=1,T=n;
	int a,b,v;
	long long k=1007;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&v);
		_connect(a,b,v*k+1);
	}
	while (BFS())
		ans+=DFS(S,INF);
	memset(vis,0,sizeof vis);
	printf("%d %d\n",ans/k,ans%k);
	return 0;
}