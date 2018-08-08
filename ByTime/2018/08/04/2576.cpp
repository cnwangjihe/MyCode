#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int _head[MAXN],_next[MAXN*2],_node[MAXN*2],_val[MAXN*2];
int col[MAXN];
int fp=0;
int n,q;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int k,int fa,int c)
{
	if (k<0)
		return ;
	int v;
	col[u]=c;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,k-_val[i],u,c);
	}
	return ;
}

int main()
{
	freopen("2576.in","r",stdin);
	freopen("2576.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,z,type;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%d",&type);
		if (type-1)
		{
			scanf("%d",&x);
			printf("%d\n",col[x]);
		}
		else
		{
			scanf("%d%d%d",&x,&y,&z);
			dfs(x,y,0,z);
		}
	}
	return 0;
}