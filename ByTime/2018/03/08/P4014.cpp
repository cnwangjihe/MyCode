#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int cx[] = {-1,-1,-1,0,0,1,1,1},
		  cy[] = {-1,0,1,-1,1,-1,0,1};

const int MAXN = 109,
		  MAXP = MAXN*2,
		  MAXE = MAXN*MAXN*2,
		  INF  = 0x7fffffff;

int _next[MAXE*2],_node[MAXE*2],_val[MAXE*2],_head[MAXP],_cost[MAXE*2];
bool _in[MAXP];
int from[MAXP],line[MAXP],dis[MAXP];
int v[MAXN][MAXN];
int n,fp=0,S,T,ans=0;


void _add(int a,int b,int v,int c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v,int c)
{
	_add(a,b,v,c);
	_add(b,a,0,-c);
	return ;
}

bool SPFA()
{
	int head=0,tail=0,u,v;
	memset(dis,0x3f,sizeof dis);
	memset(from,-1,sizeof from);
	memset(_in,0,sizeof _in);
	line[tail++]=S;
	dis[S]=0;
	_in[S]=1;
	while (head!=tail)
	{
		u=line[head++];
	//	cerr << dis[u] << endl;
		head%=MAXP;
		for (int i=_head[u];~i;i=_next[i])
		{
			if (_val[i]<=0)
				continue;
			v=_node[i];
			if (dis[v]>dis[u]+(long long)_cost[i])
			{
				dis[v]=dis[u]+(long long)_cost[i],from[v]=i;
				if (!_in[v])
					_in[v]=1,line[tail++]=v,tail%=MAXP;
			}
		}
		_in[u]=0;
	}
	return (~from[T]);
}

int _getcost()
{
	int flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
//	flowsum+=flow;
	return dis[T]*flow;
		
}

int main()
{
	scanf("%d",&n);
	memset(_head,-1,sizeof _head);
	S=0,T=n*2+1;
	for (int i=1;i<=n;i++)
		_connect(S,i,1,0),_connect(i+n,T,1,0);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&v[i][j]);
			_connect(i,j+n,1,v[i][j]);
		}
	}
	while (SPFA())
		ans+=_getcost();
	printf("%lld\n",ans);
	memset(_head,-1,sizeof _head);
	fp=0;
	for (int i=1;i<=n;i++)
		_connect(S,i,1,0),_connect(i+n,T,1,0);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			_connect(i,j+n,1,-v[i][j]);
	}
	ans=0;
	while (SPFA())
		ans+=_getcost();
	printf("%lld\n",-ans);
}
