#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int head[2000000+20];
int dis[2000000+20];
int inq[2000000+20];
struct node
{
	int v,w,next;
}e[6000000+20];
int k;
int S,T;
void add(int u,int v,int w)
{
	e[k].v=v;
	e[k].w=w;
	e[k].next=head[u];
	head[u]=k++;
	
	e[k].v=u;
	e[k].w=w;
	e[k].next=head[v];
	head[v]=k++;
}
void spfa()
{
	memset(dis,inf,sizeof(dis));
	memset(inq,0,sizeof(inq));
	queue<int>q;
	dis[S]=0;
	inq[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=e[i].next)
		{
			int v=e[i].v;
			if(dis[u]+e[i].w<dis[v])
			{
				dis[v]=dis[u]+e[i].w;
				if(!inq[v])
				{
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	printf("%d\n",dis[T]);
}
int main()
{
	memset(head,-1,sizeof head);
	k=0;
	scanf("%d%d",&n,&m);
	if (n == 1 || m == 1)
    {
        if (n > m) swap(n, m);
        int ans = inf;
        for (int i = 1; i < m; ++i)
        {
        	int x;
            scanf("%d",&x);
            if (x < ans) ans = x;
        }
        printf("%d\n", ans);
        exit(0);
    }
	S=0,T=2*(m-1)*(n-1)+1;
	int w;
	for(int j=1;j<m;j++)
	{
		int id=j*2-1;
		scanf("%d",&w);
		add(S,id,w);
	}
	for(int i=1;i<n-1;i++)
	{
		for(int j=1;j<m;j++)
		{
			int t1=2*((i-1)*(m-1)+j);
			int t2=2*(i*(m-1)+j)-1;
			scanf("%d",&w);
			add(t1,t2,w);
		}
	}
	for(int j=1;j<m;j++)
	{
		int id=2*((n-2)*(m-1)+j);
		scanf("%d",&w);
		add(id,T,w);
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&w);
			if(j==1)
			{
				int id=2*(i*(m-1)+j);
				add(id,T,w);
			}
			else if(j==m)
			{
				int id=2*((i+1)*(m-1))-1;
				add(S,id,w); 
			}
			else
			{
				int t1=2*(i*(m-1)+j-1)-1;
				int t2=2*(i*(m-1)+j);
				add(t1,t2,w);
			}
		}
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=1;j<m;j++)
		{
			scanf("%d",&w);
			int t1=2*(i*(m-1)+j)-1;
			int t2=2*(i*(m-1)+j);
			add(t1,t2,w);
		}
	}
	spfa(); 
	return 0;
}