#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 70000;

int _head[MAXN*2],_next[MAXN*4],_node[MAXN*4];
int cnt[MAXN],ans[MAXN];
int fa[MAXN],f[MAXN][17],dep[MAXN];
int sum[MAXN];
int q[MAXN];
int fp,n;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void BFS()
{
	int head=0,tail=0,c=0,v,u;
	for (int i=1;i<=n;i++)
		if (!cnt[i])
			q[tail++]=i;
	while (head!=tail)
	{
		u=q[head++];
		ans[++c]=u;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if(!--cnt[v]) 
				q[tail++]=v;
		}
	}
	return ;
}
void Pre(int x)
{
	f[x][0]=fa[x];
	for (int i=1;i<17;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	return ;
}
int LCA(int x,int y)
{
	if (dep[x]<dep[y])
		swap(x,y);
	for (int i=16;i>=0;i--)
		if (f[x][i] && dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if (x==y)
		return y;
	for (int i=16;i>=0;i--)
		if (f[x][i] && f[y][i] && f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return fa[x];
}

void Build()
{
	int u,v;
	dep[n+1]=1;
	fa[n+1]=n+1;
	for (int i=n;i;i--)
	{
		u=ans[i];
		if (_head[u]==-1)
		{
			fa[u]=n+1;
			_connect(n+1+n,u);
			f[u][0]=n+1;
			dep[u]=2;
			continue;
		}
		v=_node[_head[u]];
		for (int i=_next[_head[u]];~i;i=_next[i])
			v=LCA(v,_node[i]);
		fa[u]=v;
		_connect(fa[u]+n,u); 
		dep[u]=dep[fa[u]]+1;
		Pre(u);
	}
	return ;
}

void DFS(int u)
{
	sum[u]=1;
	for (int i=_head[u+n];~i;i=_next[i])
	{
		DFS(_node[i]);
		sum[u]+=sum[_node[i]];
	}
	return ;
}
int main()
{
	memset(_head,-1,sizeof _head);
	int x;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		while (x!=0)
		{
			_connect(i,x);
			++cnt[x];
			scanf("%d",&x);
		}
	}
	BFS();
	Build();
	DFS(n+1);
	for (int i=1;i<=n;i++)
		printf("%d\n",sum[i]-1);
	return 0;
}