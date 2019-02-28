// Date      : 2019-02-21 10:37:47
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

struct Graph{
	inline void _connect(int a,int b)
	{
		_next[fp]=_head[a];
		_node[fp]=b;
		_head[a]=fp++;
		return ;
	}
};

Graph Map,Tree;
map<pair<int,int> > bel;


void _getroot(int u,int fa,int sz)
{
	int v;
	s[u]=1,f[u]=0;
	for (int i=Tree._head[u];~i;i=Tree._next[i])
	{
		v=Tree._node[i];
		if (done[v] || v==fa)
			continue;
		_getroot(v,u,sz);
		s[u]+=s[v];
		f[u]=max(f[u],s[v]);
	}
	f[u]=max(f[u],sz-s[u]);
	if (f[u]<f[root])
		root=u;
	return ;
}

void bfs(int s,int dis[])
{
	queue<int> q;
	q.push_back(s);
	while (!q.empty())
	{
		u=q.front(),q.pop_front();
		for (int i=Map._head[u];~i;i=Map._next[i])
		{
			v=Map._node[i];
			if (vis[v] || disabled[v])
				continue;
			dis[v]=dis[u]+1;
			vis[v]=1;
			if (!_in[v])
				q.push_back(v),_in[v]=1;
		}
	}
	return ;
}

void solve(int u,int sz)
{
	root=0;
	_getroot(u,0,sz);
	u=root;
	for (int i=0;i<3;i++)
	{
		bfs(near)
	}

}

int main()
{
//	freopen("drive.in","r",stdin)
//	freopen("drive.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
		Map._connect(i,i+1),Map._connect(i+1,i);
	for (int i=1;i<=n;i++)
		d[i]=2;
	Map._connect(1,n),Map._connect(n,1);
	for (int i=0;i<n-3;i++)
	{
		scanf("%d%d",&x,&y);
		Map._connect(x,y),Map._connect(y,x);
		d[x]++,d[y]++;
	}
	for (int i=1;i<=n;i++)
		if (d[i]==2)
			q.push_back(i);
	while (!q.empty())
	{
		x=q.front(),q.pop_front();
		if (d[x]!=2)
			continue;
		vis[x]=1,y=-1;
		for (int i=Map._head[x];~i;i=Map._next[i])
		{
			v=Map._node[i];
			if (vis[v])
				continue;
			if (~y) z=v; else y=v;
			if (--d[v]==2)
				q.push_back(v);
		}
		u=m++;
		if (x>y)
			swap(x,y);
		if (y>z)
			swap(y,z);
		if (x>y)
			swap(x,y);
		if (bel.count(make_pair(x,y)))
			Tree._connect(u,bel[make_pair(x,y)]);
		else
			bel[make_pair(x,y)]=u;
		if (bel.count(make_pair(x,z)))
			Tree._connect(u,bel[make_pair(x,z)]);
		else
			bel[make_pair(x,z)]=u;
		if (bel.count(make_pair(y,z)))
			Tree._connect(u,bel[make_pair(y,z)]);
		else
			bel[make_pair(y,z)]=u;
		near[u]=TriNode(x,y,z);
	}
	f[0]=10000000;
	solve(1,m);
	return 0;
}