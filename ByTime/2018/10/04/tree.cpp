#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009;

int _head[MAXN],_next[MAXN*2],_node[MAXN*2],_val[MAXN*2];
long long f[MAXN][MAXN];
int size[MAXN];
int n,k,fp=0;

inline void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	long long tmp;
	size[u]=1;
	f[u][0]=f[u][1]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
		size[u]+=size[v];
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		for (int a=min(k,size[u]);~a;a--)
			for (int b=0;b<=min(a,size[v]);b++)
				if (~f[u][a-b])
				{
					tmp=1ll*b*(k-b)*_val[i] + 1ll*(size[v]-b)*(n-k+b-size[v])*_val[i];
					f[u][a]=max(f[u][a] , f[u][a-b]+f[v][b]+tmp);
				}
	}
	return ;
}


int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	memset(_head,-1,sizeof _head);
	memset(f,-1,sizeof f);
	int x,y,z;
	scanf("%d%d",&n,&k);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	dfs(1,0);
	printf("%lld\n",f[1][k]);
	return 0;
}
