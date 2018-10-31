#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MAXM = 4000009;

struct TMax{int i,v;};

int _head[MAXN*2],_next[MAXM],_node[MAXM];
int Stack[MAXN];
int dfn[MAXN],low[MAXN],bel[MAXN];
bool _in[MAXN];
TMax Max[MAXN][2];
int tim,fp,k,n,m,top,ans;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void tarjan(int u,int e_id)
{
	int v;
	dfn[u]=low[u]=++tim;
	Stack[top++]=u;
	_in[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		if ((e_id^1)==i)
			continue;
		v=_node[i];
		if (!dfn[v])
		{
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
		}
		else
		{
			if (_in[v])
				low[u]=min(low[u],dfn[v]);
		}
	}
	if (dfn[u]!=low[u])
		return ;
	k++;
	do
	{
		v=Stack[--top];
		_in[v]=0;
		bel[v]=k;
	}
	while (u!=v);
	return ;
}

void rebuild()
{
	int v;
	for (int u=1;u<=n;u++)
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (bel[v]==bel[u])
				continue;
			_connect(bel[v],bel[u]);
			_connect(bel[u],bel[v]);
		}
	return ;
}

int dfs1(int u,int fa)
{
	_in[u]=1;
	int v,w;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || _in[v])
			continue;
		w=dfs1(v,u)+1;
		if (w>Max[u][1].v)
			Max[u][1].v=w,Max[u][1].i=v;
		if (Max[u][1].v>Max[u][0].v)
			swap(Max[u][0],Max[u][1]);
	}
	return Max[u][0].v;
}

void dfs2(int u,int fa)
{
	_in[u]=1;
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || _in[v])
			continue;
		dfs2(v,u);
	}
	ans=max(ans,Max[u][0].v+Max[u][1].v);
	if (!fa)
		return ;
	if (Max[fa][0].i==u)
		ans=max(ans,Max[u][0].v+1+Max[fa][1].v);
	else
		ans=max(ans,Max[u][0].v+1+Max[fa][0].v);
	return ;
}

int main()
{
	freopen("rebuild.in","r",stdin);
	freopen("rebuild.out","w",stdout);
	int a,b;
	memset(_head,-1,sizeof _head);
	while (scanf("%d%d",&n,&m) && (n || m))
	{
		fp=0;
		k=n;ans=0;
		tim=0;top=0;
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			if (a==b)
				continue;
			_connect(a,b);
			_connect(b,a);
		}
		tarjan(1,fp+3);
	//	cerr << k << endl;
		rebuild();
	/*	for (int i=n+1;i<=k;i++)
		{
			for (int j=_head[i];~j;j=_next[j])
				printf("%d ",_node[j]);
			puts("");
		}*/
		for (int i=n+1;i<=k;i++)
			_in[i]=0;
		dfs1(n+1,0);
	/*	for (int i=n+1;i<=k;i++)
		{
			cerr << Max[i][0].v << ' ' << Max[i][1].v << endl;
		}*/
		for (int i=n+1;i<=k;i++)
			_in[i]=0;
		dfs2(n+1,0);
		printf("%d\n",k-n-1-ans);
		for (int i=1;i<=n;i++)
			dfn[i]=0;
		for (int i=n+1;i<=k;i++)
			Max[i][0].v=Max[i][1].v=Max[i][0].i=Max[i][1].i=0;
		for (int i=1;i<=k;i++)
			_head[i]=-1;
	}
	return 0;
}