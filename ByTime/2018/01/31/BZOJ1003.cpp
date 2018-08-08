#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXM = 25,
		  MAXE = MAXM*MAXM,
		  MAXN = 105;

int _next[MAXE],_head[MAXM],_node[MAXE],_val[MAXE];
int dis[MAXM],line[MAXM];
bool f[MAXM];
int ans[MAXN];
int c[MAXM][MAXN];
int n,m,K,e,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

int SPFA(int a,int b)
{
	int u,v;
	memset(f,0,sizeof f);
	memset(dis,-1,sizeof dis);
	int head=0,tail=0;
	line[tail++]=1;
	f[1]=1;
	dis[1]=0;
	while(head!=tail)
	{
		u=line[head++];
		head%=m;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (c[v][b]-c[v][a]!=b-a || (~dis[v] && dis[v]<dis[u]+_val[i]))
				continue;
			dis[v]=dis[u]+_val[i];
			if (!f[v])
			{
				f[v]=1;
				line[tail++]=v;
				tail%=m;
			}
		}
		f[u]=0;
	}
	return ~dis[m]?dis[m]*(b-a):-1;
}

int main()
{
	int x,y,z,d,tmp;
	memset(c,0,sizeof c);
	memset(ans,0x7f,sizeof ans);
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d%d",&n,&m,&K,&e);
	for (int i=0;i<e;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	scanf("%d",&d);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			c[i][j]=1;
	for (int i=0;i<d;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		for (int j=y;j<=z;j++)
			c[x][j]=0;
	}
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			c[i][j]+=c[i][j-1];
	ans[0]=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<i;j++)
		{
			tmp=SPFA(j,i);
			if (~tmp)
				ans[i]=min(ans[i],ans[j]+K+tmp);
		}
	}
	printf("%d\n",ans[n]-K);
	return 0;
}