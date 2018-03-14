#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 2009,
		  MAXP = MAXN*2,
		  MAXE = MAXN*6;

const long long INF  = (1ll)<<62;

int _next[MAXE*2],_node[MAXE*2],_head[MAXP],_cost[MAXE*2];
long long _val[MAXE*2];
bool _in[MAXP];
int from[MAXP],line[MAXP];
long long dis[MAXP];
int fp=0,S,T;
long long ans=0;

void _add(int a,int b,long long v,int c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,long long v,int c)
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
	long long flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
	return dis[T]*(long long)flow;
}

int main()
{
	int p,m,f,t,s,n,v;
	scanf("%d",&n);
	memset(_head,-1,sizeof _head);
	S=0,T=n*2+1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&v);
		_connect(S,n+i,v,0);
		_connect(i,T,v,0);
	}
	scanf("%d%d%d%d%d",&p,&m,&f,&t,&s);
	for (int i=1;i<=n;i++)
	{
		_connect(0,i,INF,p);
		if (i+m<=n)
			_connect(i+n,i+m,INF,f);
		if (i+t<=n)
			_connect(i+n,i+t,INF,s);
		if (i+1<=n)
			_connect(i,i+1,INF,0);
	}
	while (SPFA())
		ans+=_getcost();
	printf("%lld\n",ans);
}
