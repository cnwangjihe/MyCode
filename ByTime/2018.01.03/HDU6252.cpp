#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 2000,
		  MAXM = MAXN*5;

int line[MAXN],vis[MAXN];
int _next[MAXM],_node[MAXM],_head[MAXN];
long long val[MAXM],dis[MAXN];
bool _in[MAXN];
int n,m,fp;
long long x;

void _connect(int x,int y,long long z)
{
	_next[fp]=_head[x];
	_node[fp]=y;
	val[fp]=z;
	_head[x]=fp++;
	return ;
}

void reset()
{
	fp=0;
	memset(_head,-1,sizeof _head);
	memset(dis,0,sizeof dis);
	memset(vis,0,sizeof vis);
	memset(_in,0,sizeof _in);
	return ;
}

bool SPFA()
{
	int head=0,tail=0;
	line[(tail++)%n]=0;
	_in[0]=1;
	while (head<tail)
	{
		int u=line[(head++)%n];
		if (++vis[u]>n) 
			return printf("IMPOSSIBLE\n")&0;
		for (int i=_head[u];~i;i=_next[i])
		{
			if (dis[u]+val[i]>dis[_node[i]])
			{
				dis[_node[i]]=dis[u]+val[i];
				if (!_in[_node[i]])
					_in[_node[i]]=1,line[(tail++)%n]=_node[i];
			}
		}
		_in[u]=0;
	}
	for (int i=2;i<=n;i++)
		printf("%lld ",dis[i]-dis[i-1]);
	printf("\n");
	return 1;
}

int main()
{
	int ttt,A,B,C,D;
	scanf("%d",&ttt);
	for (int tt=1;tt<=ttt;tt++)
	{
		reset();
		printf("Case #%d: ",tt);
		scanf("%d%d%lld",&n,&m,&x);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d%d%d",&A,&B,&C,&D);
			_connect(A,D,x+(A!=B || C!=D));
			_connect(C,B,-x+(A!=B || C!=D));
		}
		for (int i=0;i<n;i++)
			_connect(i,i+1,1);
		SPFA();
	}
	return 0;
}
