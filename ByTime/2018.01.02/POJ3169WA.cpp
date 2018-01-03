#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 10009,
		  MAXM = 200009;

int fp=0;
bool vis[MAXN];
int _node[MAXM],_head[MAXN],_next[MAXM],val[MAXM];
long long sum[MAXN];
bool reach=0;

void _connect(int x,int y,int z)
{
	_next[fp]=_head[x];
	_node[fp]=y;
	val[fp]=z;
	_head[x]=fp++;
	return ;
}

bool dfs(int u,int tar,long long s)
{
	if (vis[u])
	{
		cerr << u << ' ' << sum[u] << ' ' << s << '\n';
		if (s-sum[u]<0) exit(printf("-1\n")&0);
			else return reach|=(u==tar);
	}
	if (u==tar) reach|=1;
	sum[u]=s;
	vis[u]=1;
	for (int i=_head[u];~i;i=_next[i])
		dfs(_node[i],tar,s+(long long)val[i]);
	return 0;
}

long long SPFA(int n)
{
	int head=0,tail=0;
	long long dis[MAXN];
	int line[MAXN];
	memset(dis,0x7f,sizeof dis);
	memset(vis,0,sizeof vis);
	line[tail++]=1;
	dis[1]=0;
	while (head<tail)
	{
		int u=line[(head++)%MAXN];
		for (int i=_head[u];~i;i=_next[i])
		{
			if (dis[u]+(long long)val[i]<dis[_node[i]])
			{
				dis[_node[i]]=dis[u]+val[i];
				if (!vis[_node[i]])
					line[(tail++)%MAXN]=_node[i],vis[_node[i]]=1;
			}
		}
		vis[u]=0;
	}
	return dis[n];
}

int main()
{
	freopen("POJ3169.in","r",stdin);
	freopen("POJ3169.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,z,ml,md,n;
	scanf("%d%d%d",&n,&ml,&md);
	for (int i=2;i<=n;i++) _connect(i,i-1,0);
	for (int i=0;i<ml;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
	}
	for (int i=0;i<md;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(y,x,-z);
	}
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		for (int j=_head[i];~j;j=_next[j])
			if (vis[_node[i]])
	}
	dfs(1,n,0);
	if (!reach) return printf("-2\n")&0;
	printf("%lld\n",SPFA(n));
	return 0;
}
