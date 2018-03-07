#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <stdlib.h>


using namespace std;

struct Tline
{
	int x,y,v;
	Tline(){v=0;}
};

const int MAXN = 309,
		  MAXM = MAXN*MAXN*5,
		  INF  = 0x7fffffff;

int n,m,a,b,v,Min,ans=0,fp=0,S,T;
Tline connect[MAXM];
int line[MAXN];
int next[MAXM],head[MAXN],dis[MAXN];
bool f[MAXN];

void _add(int a,int b,int v)
{
	connect[fp].x=a;
	connect[fp].y=b;
	connect[fp].v=v;
	next[fp]=head[a];
	head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v)
{
	_add(a,b,v);
	_add(b,a,0);
}

bool BFS()
{
	int h=0,t=0,u;
	memset(f,0,sizeof f);
	line[t++]=S;
	f[S]=1;
	dis[S]=1;
	while (h<t)
	{
		u=line[h++];
		for (int i=head[u];~i;i=next[i])
			if (f[connect[i].y]==0 && connect[i].v>0)
			{
				f[connect[i].y]=1;
				dis[connect[i].y]=dis[u]+1;
	//			cerr << u << " " << connect[i].y <<'\n';
				line[t++]=connect[i].y;
			}
	}
	return f[T];
}

int DFS(int u,int Min)
{
	int ans=0,tmp;
	if (u==T)
		return Min;
//	cerr << u << endl;
	for (int i=head[u];~i;i=next[i])
	{
		if (connect[i].v==0 || dis[connect[i].y]!=dis[u]+1)
			continue;
	//	cerr << connect[i].y << ' ';
		tmp=DFS(connect[i].y,min(Min-ans,connect[i].v));
		connect[i].v-=tmp;
		connect[i^1].v+=tmp;
		ans+=tmp;
		if (ans==Min) return ans;
	}
	return ans;
}

int main()
{
	int a,b;
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	S=0,T=n+1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if (a)
			_connect(S,i,1);
		else
			_connect(i,T,1);
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b,1);
		_connect(b,a,1);
	}
	while (BFS())
	{
	//	for (int i=1;i<=n;i++)
	//		cerr << dis[i] << ' ';
	//	cerr << '\n';
		ans+=DFS(S,INF);
	//	system("pause");
	}
	printf("%d\n",ans);
	return 0;
}
