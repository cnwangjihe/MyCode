#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*2;

int _head[MAXN],_next[MAXM],_node[MAXM];
int val[MAXN],ans[MAXN],sum[MAXN],dep[MAXN];
int jump[MAXN][20];
int n,fp=0;
bool f[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int calc1000(int u,int fa,int dep,int maxdep)
{
	int ans=f[u]?0:val[u],v;
	f[u]=1;
	if (maxdep==dep)
		return ans;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		ans+=calc1000(v,u,dep+1,maxdep);
	}
	return ans;
}

void dfs1000(int u,int fa,int sum,int dep)
{
	int v;
	sum=ans[u]=calc1000(u,fa,0,dep)+sum;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs1000(v,u,sum,dep+1);
	}
	return ;
}

int _up(int u,int k)
{
	for (int i=0;(1<<i)<=k;i++)
		if (k&(1<<i))
			u=jump[u][i];
	return u;
}

int dfs1(int u,int fa)
{
	int v,tmp=val[u];
	jump[u][0]=fa;
	for (int i=1;i<18;i++)
		jump[u][i]=jump[jump[u][i-1]][i-1];
	sum[u]=val[u];
	dep[u]=dep[fa]+1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		sum[u]+=dfs1(v,u);
		tmp+=val[v];

	}
	if (dep[u]&1)
		sum[_up(u,dep[u]/2)]-=tmp;
	return sum[u];
}


void dfs2(int u,int s)
{
	int v;
	ans[u]=s+val[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (jump[u][0]==v)
			continue;
		ans[u]+=sum[v];
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (jump[u][0]==v)
			continue;
		dfs2(v,ans[u]-sum[v]);
	}
	return ;
}

int main()
{
	freopen("danger.in","r",stdin);
	freopen("danger.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int a,b;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	dep[0]=-1;
	if (n<=1000)
		dfs1000(1,0,0,0);
	else
		dfs1(1,0),dfs2(1,0);
	for (int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}