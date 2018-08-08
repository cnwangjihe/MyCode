#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 200009,
		  INF  = 1000000009;

const int cx[]={-1,-2,-2,-1,1,2,2,1},
		  cy[]={-2,-1,1,2,2,1,-1,-2};

int _next[MAXM*2],_node[MAXM*2],_head[MAXN],_head1[MAXN],_val[MAXM*2];
bool vis[MAXN];
int line[MAXN],dis[MAXN];
int fp=0,S,T,n,m,ans=0;
int c[300][300],a[300][300];

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
	for (int &i=_head1[u];~i;i=_next[i])
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
	int x,y,nx,ny;
	scanf("%d%d",&n,&m);
	S=0,T=n*n+1;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		c[x][y]=1;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			a[i][j]=(i-1)*n+j;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (c[i][j])
				continue;
			if ((i+j)&1)
			{
				_connect(S,a[i][j],1);
				for (int k=0;k<8;k++)
				{
					nx=i+cx[k],ny=j+cy[k];
					if (nx>=1 && nx<=n && ny>=1 && ny<=n)
						_connect(a[i][j],a[nx][ny],INF);
				}
			}
			else 
				_connect(a[i][j],T,1);
		}
	ans=n*n-m;
	while (BFS())
	{
		memcpy(_head1,_head,sizeof _head);
		ans-=DFS(S,INF);
	}
	printf("%d\n",ans);
	return 0;
}