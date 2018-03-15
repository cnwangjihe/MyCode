#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

int n,m,a,b,t;
int _node[100],_head[100],_next[100];
int fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}
//x+2(1-x)=(t+1)x+(1-x)
int dfs(int u,int t,int s)
{
	if (u==t)
		return s;
	int f=1000000;
	for (int i=_head[u];~i;i=_next[i])
		f=min(f,dfs(_node[i],t,s+1));
	return f;
}

int main()
{
	freopen("die.in","r",stdin);
	freopen("die.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&t);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
	}
	int tmp=dfs(b,a,0);
	if (tmp==1000000)
	{
		printf("%d.000\n",t+1);
		return 0;
	}
	if (_head[a]==-1)
	{
		printf("%d.000\n",min(t+1,tmp));
		return 0;
	}
	printf("%.3f\n",(double)(2.00*t+1)/(t+1.00));
	return 0;
}