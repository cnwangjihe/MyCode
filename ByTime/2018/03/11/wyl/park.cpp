#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 20005,
		  MAXM = 25005,
		  INF  = 100000009;

int power[16],f[16][MAXM*3];
int val[MAXN],dep[MAXN],tmp[MAXN];
int _head[MAXN],_next[MAXM*2],_node[MAXM*2];
bool vis[MAXN];
int n,m,ans,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
	vis[u]=1;
	int cnt=0;
	if (!dep[u])
	{
		f[0][0]=val[u];
		f[0][1]=0;
		f[0][2]=INF;
	}
	else
	{
		for (int i=_head[u];~i;i=_next[i])
			if (vis[_node[i]] && dep[_node[i]]<dep[u])
				tmp[++cnt]=dep[_node[i]];
		for (int i=0;i<power[dep[u]+1];i++)
			f[dep[u]][i]=INF;
		for (int i=0,t,l;i<power[dep[u]];i++)
		{
			t=1, l=i;
			for (int j=1;j<=cnt;j++)
				if (i/power[tmp[j]]%3==0) 
					t=2;
				else
					l+=(i/power[tmp[j]]%3==1)?power[tmp[j]]:0;
			f[dep[u]][i+t*power[dep[u]]]=min(f[dep[u]][i+t*power[dep[u]]],f[dep[u]-1][i]);
			f[dep[u]][l]=min(f[dep[u]][l],f[dep[u]-1][i]+val[u]);
		}
	}
	for (int i=_head[u];~i;i=_next[i])
		if (!vis[_node[i]])
		{
			dep[_node[i]]=dep[u]+1;
			dfs(_node[i]);
			for (int j=0;j<power[dep[u]+1];j++)
				f[dep[u]][j]=min(f[dep[u]+1][j],f[dep[u]+1][j+2*power[dep[u]+1]]);
		}
	return ;
}

int main()
{
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	int x,y;
	memset(_head,-1,sizeof _head);
	power[0]=1;
	for (int i=1;i<16;i++)
		power[i]=power[i-1]*3;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y),_connect(y,x);
	}
	for (int i=1;i<=n;i++)
		if(!vis[i])
		{
			dfs(i);
			ans+=min(f[0][0],f[0][2]);
		}
	printf("%d\n",ans);
	return 0;
}