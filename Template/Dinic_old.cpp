#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iomanip>

using namespace std;

struct Tline{
	int x,y,v;
	Tline(){v=0;}
};

const int MAXV = 10000006,
		  MAXN = 206,
		  MAXM = 406,
		  INF = 2000000000;

int n,m,a,b,v,Min,ans=0,fp=0;
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
	head[a]=fp;
	fp++;
}

bool BFS()
{
	int h=0,t=0;
	memset(f,0,sizeof f);
	line[t++]=1;f[1]=1;
	dis[1]=0;
	while (h<t)
	{
		for (int i=head[line[h]];i!=-1;i=next[i])
			if (f[connect[i].y]==0 && connect[i].v>0)
			{
				f[connect[i].y]=1;
				dis[connect[i].y]=dis[line[h]]+1;
				line[t++]=connect[i].y;
			}
		h++;
	}
	return f[n];
}

int DFS(int root,int Min)
{
	int ans=0,tmp;
	if (root==n) {return Min;}
	for (int i=head[root];i!=-1;i=next[i])
	{
		if (connect[i].v==0 || dis[connect[i].y]!=dis[root]+1) continue;
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
	scanf("%d%d",&m,&n);
	memset(head,-1,sizeof head);
	memset(next,-1,sizeof next);
	fp=0;ans=0;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&v);
		_add(a,b,v);
		_add(b,a,0);
	}
	while (BFS())
	{
	//	for (int i=1;i<=n;i++) cout << dis[i] << ' ';cout << endl;
		Min=MAXV;
		ans+=DFS(1,INF);
	}
	printf("%d\n",ans);
}