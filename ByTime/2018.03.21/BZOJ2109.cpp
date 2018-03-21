#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <queue>
#include <vector>


using namespace std;

const int MAXN = 40009,
		  MAXM = 40009;

priority_queue < pair<int,int> > q;
int _next[MAXM],_node[MAXM],_head[MAXN];
int k[MAXN],cnt[MAXN],tcnt[MAXN],ans[MAXN];
int n,m,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void BFS()
{
	int c=n,u,v;
	memcpy(tcnt,cnt,sizeof cnt);
	for (int i=1;i<=n;i++)
		if (!tcnt[i])
			q.push(make_pair(k[i],i));
	while (!q.empty())
	{
		u=q.top().second;
		q.pop();
		ans[c--]=u;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (!--tcnt[v])
				q.push(make_pair(k[v],v));
		}
	}
	return ;
}

int Calc(int x)
{
	int c=n,u,v;
	memcpy(tcnt,cnt,sizeof cnt);
	priority_queue < pair<int,int> > q;
	for (int i=1;i<=n;i++)
		if (!tcnt[i] && x!=i)
			q.push(make_pair(k[i],i));
	while (!q.empty())
	{
		u=q.top().second;
	//	ans[c--]=u;
		if (q.top().first<c)
			return c;
		q.pop();
		c--;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (!--tcnt[v] && v!=x)
				q.push(make_pair(k[v],v));
		}
	}
	return c;
}

int main()
{
//	freopen("BZOJ2535.in","r",stdin);
	int a,b;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&k[i]);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		cnt[a]++; 
		_connect(b,a);
	}
	BFS();
//	for (int i=1;i<=n;i++)
//		printf("%d%c",ans[i],i==n?'\n':' ');
	for (int i=1;i<=n;i++)
		printf("%d%c",Calc(i),i==n?'\n':' ');
	return 0;
}