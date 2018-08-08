#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 109,
		  MAXP = MAXN*2,
		  MAXE = MAXP*MAXP,
		  INF  = 0x7fffffff;
const double DINF = 100009,
			 eps  = 1e-9;

int _next[MAXE*2],_node[MAXE*2],_val[MAXE*2],_head[MAXP];
double _cost[MAXE*2];
bool _in[MAXP];
int from[MAXP],line[MAXP];
double dis[MAXP];
int a[MAXN][MAXN],b[MAXN][MAXN];

int n,m,fp=0,S,T,ans=0,sum=0;

void _add(int a,int b,int v,double c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v,double c)
{
	_add(a,b,v,c);
	_add(b,a,0,-c);
	return ;
}

bool SPFA()
{
	int head=0,tail=0,u,v;
	for (int i=0;i<MAXP;i++)
		dis[i]=-DINF;
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
			if (!_val[i])
				continue;
			v=_node[i];
			if (dis[v]<dis[u]+_cost[i])
			{
				dis[v]=dis[u]+_cost[i],from[v]=i;
				if (!_in[v])
					_in[v]=1,line[tail++]=v,tail%=MAXP;
			}
		}
		_in[u]=0;
	}
//	cerr << dis[T] << endl;
	return (~from[T]);
}

double _getcost()
{
	int flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
	return dis[T]*(double)flow;	
}

bool _check(double k)
{
	memset(_head,-1,sizeof _head);
	S=0,T=2*n+1;
	fp=0;
	for (int i=1;i<=n;i++)
	{
		_connect(S,i,1,0),_connect(i+n,T,1,0);
		for (int j=1;j<=n;j++)
			_connect(i,j+n,1,(double)a[i][j]-k*(double)b[i][j]);
	}
	double ans=0.0;
	while (SPFA())
		ans+=_getcost();
//	cerr << ans << endl;
	return ans>eps;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	double l=0,r=10000,mid;
//	_check(100);
	while (l+eps<r)
	{
		mid=(l+r)/2.0;
		if (_check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.6f\n",l);
	return 0;
}
