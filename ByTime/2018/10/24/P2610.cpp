#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009;

map < pair<int,int> ,int > edge;
map < pair<int,int> ,bool > mp;
int _head[MAXN],_node[MAXN*6],_next[MAXN*6];
int Max[MAXN][2];
bool vis[MAXN];
int n,fp=0;

inline void _sort(int &a,int &b,int &c)
{
	if (a>b)
		swap(a,b);
	if (a>c)
		swap(a,c);
	if (b>c)
		swap(b,c);
	return ;
}

inline void _connect(int a,int b)
{
	if (mp.count(make_pair(a,b)))
		return ;
	mp[make_pair(a,b)]=1;
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int dfs1(int u)
{
	vis[u]=1;
	int t=0,v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (vis[v])
			continue;
		Max[u][t++]=dfs1(v)+1;
	}
//	cerr << u << ' ' << Max[u][0] << ' ' << Max[u][1] << '\n';
	return max(Max[u][0],Max[u][1]);
}

int dfs2(int u,int fa,bool c)
{
	vis[u]=1;
	int t=0,ans=0,v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (vis[v])
			continue;
		ans=max(ans,dfs2(v,u,t++));
	}
	ans=max(ans,Max[u][0]+Max[u][1]+1);
	if (fa)
		ans=max(ans,max(Max[u][0],Max[u][1])+Max[fa][c^1]+2);
	return ans;
}

int main()
{
	int a,b,c;
	pair<int,int> p;
	memset(_head,-1,sizeof _head);
	memset(Max,0,sizeof Max);
	scanf("%d",&n);
	n-=2;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		_sort(a,b,c);
		p=make_pair(a,b);
		if (edge.count(p))
			_connect(i,edge[p]),_connect(edge[p],i);
		else
			edge[p]=i;
		p=make_pair(a,c);
		if (edge.count(p))
			_connect(i,edge[p]),_connect(edge[p],i);
		else
			edge[p]=i;
		p=make_pair(b,c);
		if (edge.count(p))
			_connect(i,edge[p]),_connect(edge[p],i);
		else
			edge[p]=i;
	}
	memset(vis,0,sizeof vis);
	dfs1(1);
	memset(vis,0,sizeof vis);
	printf("%d\n",dfs2(1,0,0));
	return 0;
}