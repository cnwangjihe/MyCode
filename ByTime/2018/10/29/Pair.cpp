#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509,
		  MAXM = (MAXN*MAXN)*2,
		  INF  = MAXN*2;

int _head[MAXN],_next[MAXM],_node[MAXM],_val[MAXM];
int dis[MAXN],line[MAXN];
bool vis[MAXN];
int S,T,fp=0;
int n,m,k,ans=0;

inline void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

inline void _addedge(int a,int b,int v)
{
	_connect(a,b,v);
	_connect(b,a,0);
	return ;
}

bool bfs()
{
	memset(vis,0,sizeof vis);
	memset(dis,-1,sizeof dis);
	int h=0,t=0,u,v;
	line[t++]=S;
	vis[S]=1;
	while (h!=t)
	{
		u=line[h++];
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (vis[v] || !_val[i])
				continue;
			dis[v]=dis[u]+1;
			line[t++]=v;
			vis[v]=1;
		}
	}
	return dis[T]!=-1;
}

int dfs(int u,int Min)
{
	int v,tmp,ans=0;
	if (u==T)
		return Min;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (!_val[i] || dis[v]!=dis[u]+1)
			continue;
		tmp=dfs(v,min(Min,_val[i]));
		_val[i]-=tmp;
		_val[i^1]+=tmp;
		ans+=tmp;
		Min-=tmp;
		if (!Min)
			return ans;
	}
	return ans;
}

int main()
{
	freopen("Pair.in","r",stdin);
	freopen("Pair.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int t;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&t);
			if (t)
				_addedge(j+2*n,i,1);
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=k;j++)
		{
			scanf("%d",&t);
			if (t)
				_addedge(i+n,j+2*n+m,1);
		}
	}
	S=0,T=2*n+m+k+1;
	for (int i=1;i<=n;i++)
		_addedge(i,i+n,1);
	for (int i=1;i<=m;i++)
		_addedge(S,i+2*n,1);
	for (int i=1;i<=k;i++)
		_addedge(i+2*n+m,T,1);
	while (bfs())
		ans+=dfs(S,INF);
	printf("%d\n",ans);
	return 0;
}