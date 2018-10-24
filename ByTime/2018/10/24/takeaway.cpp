#include <bits/stdc++.h>

using namespace std;

const long long INF = 1000000000000000ll;

const int MAXN = 3009,
		  MAXM = 70009;

int _head[MAXN],_next[MAXM+MAXN*MAXN],_node[MAXM+MAXN*MAXN],_val[MAXM+MAXN*MAXN];
int vis[MAXN],cnt[MAXN];
int k[MAXN],d[MAXN][MAXN];
long long f[MAXN],g[MAXN];
bool _in[MAXN];
int fp=0,n,m;

priority_queue<pair<int,int>,vector< pair<int,int> >,greater< pair<int,int> > >q;

inline void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

long long bfs(int n)
{
	int u,v;
	long long sum,w;
	memset(f,127/3,sizeof f);
	memset(g,0,sizeof g);
	q.push(make_pair(0,1));
	f[1]=0;
	while (!q.empty())
	{
		u=q.top().second;
		q.pop();
		if (_in[u])
			continue;
		_in[u]=1;
		w=max(f[u],g[u]);
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (w+_val[i]<f[v])
			{
				f[v]=w+_val[i];
				sum=max(f[v],g[v]);
				if (!cnt[v])
					q.push(make_pair(sum,v));
			}
		}
		for(int i=0;i<k[u];i++)
		{
			v=d[u][i];
			cnt[v]--;
			g[v]=max(g[v],w);
			sum=max(f[v],g[v]);
			if (!cnt[v])
				q.push(make_pair(sum,v));
		}
	}
	return max(f[n],g[n]);
}

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
	return x*f;
}
/*
long long dfs(int u)
{
//	cerr << u << endl;
	if (~f[u])
		return f[u];
	if (vis[u]==500)
		return f[u]=INF;
	vis[u]++;
	int v;
	long long Min=INF,Max=-1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (_val[i])
		{
			if (~f[v])
				Min=min(Min,f[v]+1ll*_val[i]);
			else
				Min=min(Min,dfs(v)+1ll*_val[i]);
		}
		else
		{
			if (~f[v])
				Max=max(Max,f[v]);
			else
				Max=max(Max,dfs(v));
		}
	}
	if (vis[u]>3)
		_in[u]=1;
	f[u]=max(Min,Max);
	return f[u];
}
*/

int main()
{
	freopen("takeaway.in","r",stdin);
	freopen("takeaway.out","w",stdout);
	int a,b,v;
	memset(_head,-1,sizeof _head);
	memset(f,-1,sizeof f);
	n=read(),m=read();
	for (int i=0;i<m;i++)
	{
		a=read(),b=read(),v=read();
		if (a==b)
			continue;
		_connect(a,b,v);
	}
	for (int i=1;i<=n;i++)
	{
		cnt[i]=read();
		for (int j=0;j<cnt[i];j++)
		{
			a=read();
			d[a][k[a]++]=i;
		}
	}
//	cerr << "Read Done!" << endl;
	printf("%lld\n",bfs(n));
	return 0;
}