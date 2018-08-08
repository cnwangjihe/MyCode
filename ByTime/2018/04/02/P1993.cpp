#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 10009,
		  MAXM = MAXN*8;

int _head[MAXN],_node[MAXM],_val[MAXM],_next[MAXM];
bool _in[MAXN];
int dis[MAXN];
int n,m,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

bool dfs(int u)
{
	_in[u]=1;
	bool f=1;
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (dis[v]<dis[u]+_val[i])
		{
			if (_in[v])
				return 0;
			dis[v]=dis[u]+_val[i];
			if (!dfs(v))
				return 0;
		}
	}
	_in[u]=0;
	return 1;
}

bool check()
{
	memset(_in,0,sizeof _in);
	for (int i=1;i<=n;i++)
	{
		dis[i]=0;
		if (!dfs(i))
			return 0;
	}
}

int main()
{
	memset(_head,-1,sizeof _head);
	int type,a,b,c;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d",&type);
		if (type==1)
		{
			scanf("%d%d%d",&a,&b,&c);
			_connect(b,a,c);
		}
		if (type==2)
		{
			scanf("%d%d%d",&a,&b,&c);
			_connect(a,b,-c);
		}
		if (type==3)
		{
			scanf("%d%d",&a,&b);
			_connect(a,b,0);
			_connect(b,a,0);
		}
	}
	printf("%s\n",check()?"Yes":"No");
	return 0;
}