#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

const int MAXN = 300008;

struct Tnode
{
	int u,v,id,next;
}edge[MAXN*2];

int color[MAXN],head[MAXN];
bool vis[MAXN];
int n,m,s,cnt=0;

void addedge(int u,int v,int id)
{
	edge[cnt].u=u;
	edge[cnt].v=v;
	edge[cnt].id=id;
	edge[cnt].next=head[u];
	head[u]=cnt++;
	return ;
}
int bfs1(int st)
{
	int ans = 1;
	queue<int> line;
	memset(vis,0,sizeof vis);
	line.push(st);
	vis[st] = 1;
	while (!line.empty())
	{
		int u = line.front();
		line.pop();
		for (int i=head[u];~i;i = edge[i].next)
		{
			if (vis[edge[i].v]) continue;
			if (edge[i].id!=-1)
				color[edge[i].id>>1] = (edge[i].id&1);
			line.push(edge[i].v);
			vis[edge[i].v] = 1;
			ans++;
		}
	}
	return ans;
}
int bfs2(int st)
{
	int ans = 1;
	queue<int> line;
	memset(vis,0,sizeof vis);
	line.push(st);
	vis[st] = 1;
	while (!line.empty())
	{
		int u = line.front();
		line.pop();
		for (int i=head[u];~i;i = edge[i].next)
		{
			if (vis[edge[i].v]) continue;
			if (edge[i].id!=-1)
			{
				color[edge[i].id>>1] = 1^(edge[i].id&1);
				continue;
			}
			line.push(edge[i].v);
			vis[edge[i].v] = 1;
			ans++;
		}
	}
	return ans;
}
int main()
{
	freopen("2350.in","r",stdin);
	freopen("2350.out","w",stdout);
	memset(head,-1,sizeof head);
	int op,u,v,pos=0;
	scanf("%d%d%d",&n,&m,&s);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&op,&u,&v);
		if (op&1)
			addedge(u,v,-1);
		else
		{
			addedge(u,v,pos);
			addedge(v,u,pos+1);
			pos+=2;
		}
	}
	printf("%d\n",bfs1(s));
	for (int i=0;i<pos/2;i++)
		putchar(color[i]?'-':'+');
	putchar('\n');
	printf("%d\n",bfs2(s));
	for(int i=0;i<pos/2;i++)
		putchar(color[i]?'-':'+');
	return 0;
}
