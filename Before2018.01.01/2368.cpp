#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <queue>

using namespace std;

const int MAXN = 1005;

int tot,n;
int dis[MAXN],head[MAXN];
int ds[MAXN][MAXN];

queue<int>q;

struct Tway
{
	int u,v,nex;
};
Tway e[MAXN*MAXN*2];

void add(int u,int v)
{
	++tot;
	e[tot].u=u;e[tot].v=v;
	e[tot].nex=head[u];head[u]=tot;
	++tot;
	e[tot].u=v;e[tot].v=u;
	e[tot].nex=head[v];head[v]=tot;	
}

int gcd(int a,int b)
{
	if(a%b==0)
		return b;
	return gcd(b,a%b);
}

int xxx=0;
void bfs(int beg)
{
	while(!q.empty())
		q.pop();
	q.push(beg);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[v]==0)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}

	}
	for(int i=1;i<=n;++i)
		ds[beg][i]=dis[i];
}

int main()
{
	freopen("2368.in","r",stdin);
	freopen("2368.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;++i)
		for(int j=i+1;j<=n;++j)
			if(gcd(i,j)!=1)
			{
				add(i,j);
			}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			dis[j]=0;
		bfs(i);
	}
	int ans=0;
	for(int i=1;i<n;++i)
		for(int j=i+1;j<=n;++j)
			ans+=ds[i][j];
	printf("%d\n",ans);
	return 0;
}
