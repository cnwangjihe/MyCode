#include <bits/stdc++.h>

using namespace std;

const int MAXK = 63,
		  MAXN = 50009,
		  MAXM = 100009*2;

long long ans=0;
long long b[MAXK],dis[MAXN];
int _head[MAXN],_node[MAXM],_next[MAXM];
long long _val[MAXM];
bool vis[MAXN];
int n,m,fp=0;

void _connect(int a,int b,long long v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void _add(long long v)
{
//	cerr << "## " << v << "  ";
	for (int i=MAXK-1;~i;i--)
	{
		if (!(v&(1ll<<i)))
			continue;
		if (b[i])
			v^=b[i];
		else
		{
//			cerr << i << endl;
			b[i]=v;
			for (int j=i-1;~j;j--)
				if (b[j] && (b[i]&(1ll<<j)))
					b[i]^=b[j];
			for (int j=i+1;j<MAXK;j++)
				if (b[j]&(1ll<<i))
					b[j]^=b[i];
			break;
		}
	}
	return ;
}

void dfs1(int u,int s)
{
	int v;
	vis[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		if ((i^1)==s)
			continue;
		v=_node[i];
		if (vis[v])
			_add(dis[u]^dis[v]^_val[i]);
		else
		{
			dis[v]=dis[u]^_val[i];
			dfs1(v,i);
		}
	}
	return ;
}

void dfs2(int u,long long s)
{
	vis[u]=1;
	if (u==n)
	{
		for (int i=MAXK-1;~i;i--)
		{
			if (!(s&(1ll<<i)))
				s^=b[i];
		}
		ans=max(ans,s);
		return ;
	}
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (vis[v])
			continue;
		dfs2(v,s^_val[i]);
	}
	return ;
}

int main()
{
	int x,y;
	long long z;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%lld",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	memset(vis,0,sizeof vis);
	dfs1(n,0);
	memset(vis,0,sizeof vis);
	dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}