#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 109,
		  MAXP = MAXN*2,
		  MAXE = MAXN*MAXN*3,
		  INF  = 0x7fffffff;

int _next[MAXE*2],_node[MAXE*2],_val[MAXE*2],_head[MAXP],_cost[MAXE*2];
bool _in[MAXP];
int from[MAXP],line[MAXP];
long long dis[MAXP];
int a[MAXN],b[MAXN],c[MAXN][MAXN];
int n,m,fp=0,S,T;
long long ans=0;


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
			if (_val[i]<=0ll)
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

long long _getcost()
{
	int flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
//	flowsum+=flow;
	return dis[T]*(long long)flow;
		
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(_head,-1,sizeof _head);
	S=0,T=n+m+1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		_connect(S,i,a[i],0);
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		_connect(i+n,T,b[i],0);
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&c[i][j]);
			_connect(i,j+n,INF,c[i][j]);
		}
	while (SPFA())
		ans+=_getcost();
	printf("%lld\n",ans);
	memset(_head,-1,sizeof _head);
	fp=0;ans=0ll;
	for (int i=1;i<=n;i++)
		_connect(S,i,a[i],0);
	for (int i=1;i<=m;i++)
		_connect(i+n,T,b[i],0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			_connect(i,j+n,INF,-c[i][j]);
	while (SPFA())
		ans+=_getcost();
	printf("%lld\n",-ans);
	return 0;	
}
