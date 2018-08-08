#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string.h>

using namespace std;

const int MAXN = 109,
		  MAXP = (1<<20)+2;

struct Tfix
{
	int bp,bj,fp,fj,cost;
};

Tfix fix[MAXN];
int line[MAXP],dis[MAXP];
bool _in[MAXP];
int n,m,S,T;
char c;

int SPFA()
{
	memset(dis,0x3f,sizeof dis);
	memset(_in,0,sizeof _in);
	int head=0,tail=0,u,v;
	line[tail++]=S;
	_in[S]=1;
	dis[S]=0;
	while (head!=tail)
	{
		u=line[head++];
		head%=MAXP;
		for(int i=1;i<=m;i++)
		{
			if ( ((~u)&fix[i].bp) || (u&fix[i].bj) )
				continue;
			v=(u|fix[i].fp)&(~fix[i].fj);
			if (dis[v]>dis[u]+fix[i].cost)
			{

				dis[v]=dis[u]+fix[i].cost;
				if(!_in[v])
					_in[v]=1,line[tail++]=v,tail%=MAXP;
			}
		}
		_in[u]=0;
	}
	return dis[T]==0x3f3f3f3f?0:dis[T];
}

int main()
{
	scanf("%d%d",&n,&m);
	S=(1<<n)-1,T=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&fix[i].cost);
		c=getchar();
		for (int j=1;j<=n;j++)
		{
			c=getchar();
			if (c=='+') fix[i].bp+=1<<(n-j);
			if (c=='-') fix[i].bj+=1<<(n-j);
		}
		c=getchar();
		for (int j=1;j<=n;j++)
		{
			c=getchar();
			if (c=='+') fix[i].fp+=1<<(n-j);
			if (c=='-') fix[i].fj+=1<<(n-j);
		}
	}
	printf("%d\n",SPFA());
	return 0;
}
