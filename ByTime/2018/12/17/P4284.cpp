// Date    : 2018-12-17 15:39:46
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500009,
		  MAXM = MAXN*2;

int _head[MAXN],_next[MAXM],_node[MAXM],_val[MAXM];
double f[MAXN],g[MAXN];
int p[MAXN];
double ans=0;
int n,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs1(int u,int fa)
{
	int v;
	f[u]=1-0.01*p[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs1(v,u);
		f[u]*=f[v]+(1-f[v])*(1-0.01*_val[i]);
	}
	return ;
}

void dfs2(int u,int fa)
{
	int v;
	double tmp;
	ans+=1-g[u]*f[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		tmp=f[u]*g[u]/(f[v]+(1-f[v])*(1-0.01*_val[i]));
		g[v]=tmp+(1-tmp)*(1-0.01*_val[i]);
		dfs2(v,u);
	}
	return ;
}

int main()
{
//	freopen("P4284.in","r",stdin);
//	freopen("P4284.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,z;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	for (int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	g[1]=1;
	dfs1(1,0);
	dfs2(1,0);
	printf("%.6lf\n",ans);
	return 0;
}