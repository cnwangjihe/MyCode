// Date      : 2019-01-11 23:30:14
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;


const int MAXN = 500009;

struct edge{
	int u,v;
}e[MAXN];

int n,a[MAXN];
vector<int> V[MAXN];

void init()
{
	int x;

	for (int i=0;i<n-1;i++)
	{
		x=__gcd(a[e[i].u],a[e[i].v]);
		for (int j=2;j*j<=x;j++)
			if(!(x%j))
			{
				V[j].push_back(i);
				while (!(x%j))
					x/=j;
			}
		if (x!=1)
			V[x].push_back(i);
	}
}

int ans;

struct Graph{
	struct edge{
		int v,n;
	}e[MAXN];
	int q[MAXN];
	vector<int> V;
	int head[MAXN],en;
	int vis[MAXN],dis[MAXN];

	void clear()
	{
		while (V.size())
			head[V.back()]=0,V.pop_back();
		en=1;
	}
	inline void connect(int u,int v)
	{
		e[en].v=v;e[en].n=head[u];head[u]=en++;
		e[en].v=u;e[en].n=head[v];head[v]=en++;
		V.push_back(u);V.push_back(v);
	}

	void bfs(int S)
	{
		if(~vis[S]) return;

		int u,i;
		int h=0,tail=0;
		vis[S]=1;
		q[tail++]=S;
		while (h!=tail)
		{
			u=q[h++];
			for (int i=head[u];i;i=e[i].n) if(!~vis[e[i].v])
			{
				vis[e[i].v]=vis[u]+1;
				q[tail++]=e[i].v;
			}
		}
		q[tail++]=u;
		dis[u]=1;
		while (h!=tail)
		{
			u=q[h++];
			for (int i=head[u];i;i=e[i].n) if(!~dis[e[i].v])
			{
				dis[e[i].v]=dis[u]+1;q[tail++]=(e[i].v);
			}
		}
		ans=max(ans,dis[u]);
	}

	void solve()
	{
		int i;

		for (int i=0;i<(int)V.size();i++) vis[V[i]]=dis[V[i]]=-1;
		for (int i=0;i<(int)V.size();i++) bfs(V[i]);
	}
}G;

void solve()
{
	ans=1;int i,j;
	for (int i=2;i<MAXN;i++)
	{
		G.clear();
		for (int j=0;j<(int)V[i].size();j++)
			G.connect(e[V[i][j]].u,e[V[i][j]].v);
		G.solve();
	}
}

int main()
{


	int i;

	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (i=1;i<=n;i++)
		if(a[i]>1)
			break;
	if (i==n+1)
		return printf("0\n"),0;
	int x,y;
	for (int i=0;i<n-1;i++)
	{ 
		scanf("%d%d",&x,&y);
		e[i].u=x,e[i].v=y;
		int d=__gcd(a[x],a[y]);
		for (int j=2;j*j<=x;j++)
			if (!(d%j))
			{
				V[j].push_back(i);
				while (!(d%j))
					d/=j;
			}
		if (d!=1)
			V[d].push_back(i);
	}
	solve();
	printf("%d\n",ans);

	return 0;
}