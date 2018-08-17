#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400005,
		  MAXM = 400009;

struct Tquery{int a,b,t;};

Tquery q[MAXM];
int _head[MAXN],_node[MAXM],_next[MAXM];
int bg[MAXN],ed[MAXN];
int ans[MAXM],fa[MAXN];
bool f[MAXN];
vector<int> a[MAXN];
int n,m,doc,tim,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
	bg[u]=++tim;
	for (int i=_head[u];~i;i=_next[i])
		dfs(_node[i]);
	ed[u]=++tim;
	return ;
}

int _find(int u)
{
	int x=u,t;
	while (fa[u]!=u)
		u=fa[u];
	while (fa[x]!=x)
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

int main()
{
	freopen("2633.in","r",stdin);
	freopen("2633.out","w",stdout);
	memset(_head,-1,sizeof _head);
	memset(f,0,sizeof f);
	int k;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d",&q[i].t);
		if (q[i].t==1)
		{
			scanf("%d%d",&q[i].a,&q[i].b);
			f[q[i].a]=1;
			_connect(q[i].b,q[i].a);
		}
		if (q[i].t==2)
			scanf("%d",&q[i].a);
		if (q[i].t==3)
		{
			scanf("%d%d",&q[i].a,&q[i].b);
			a[q[i].b].push_back(i);
		}
	}
	for (int i=1;i<=n;i++)
		if (!f[i])
			dfs(i);
/*	for (int i=1;i<=n;i++)
		cerr << bg[i] << ' ' << ed[i] << '\n';*/
	for (int i=1;i<=n;i++)
		fa[i]=i;
	doc=0;
	for (int i=0;i<m;i++)
	{
		if (q[i].t==1)
			fa[_find(q[i].a)]=_find(q[i].b);
		if (q[i].t==2)
		{
			doc++;
			for (int j=0;j<(int)a[doc].size();j++)
			{
				k=a[doc][j];
				if ( !(bg[q[k].a]<=bg[q[i].a] && ed[q[k].a]>=ed[q[i].a]) )
					ans[k]=0;
				else
					ans[k]=(_find(q[k].a)==_find(q[i].a));
			}
		}
	}
	for (int i=0;i<m;i++)
		if (q[i].t==3)
			printf("%s\n",ans[i]?"YES":"NO");
	return 0;
}