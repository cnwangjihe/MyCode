#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10009,
		  MAXM = 50500*2,
		  MAXK = 22,
		  INF  = 2000000000;

struct Tedge{int a,b,v;};

Tedge e[MAXM];
int _head[MAXN],_next[MAXM],_node[MAXM],_val[MAXM];
int jump[MAXN][MAXK],Min[MAXN][MAXK];
int fa[MAXN],deep[MAXN];
int n,m,q,fp=0;


void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

int _find(int u)
{
	int x=u,t;
	while (u!=fa[u])
		u=fa[u];
	while (x!=fa[x])
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

bool _cmp(Tedge a,Tedge b){return a.v>b.v;}

void dfs(int u,int fa,int w)
{
	int v;
	deep[u]=deep[fa]+1;
	jump[u][0]=fa;
	Min[u][0]=w;
	for (int i=0;jump[u][i];i++)
	{
		jump[u][i+1]=jump[jump[u][i]][i];
		Min[u][i+1]=min(Min[u][i],Min[jump[u][i]][i]);
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u,_val[i]);
	}
	return ;
}

int getlca(int a,int b)
{
	int ans=INF;
	if (deep[a]<deep[b])
		swap(a,b);
	int h=deep[a]-deep[b];
	for (int i=20;~i;i--)
		if (h&(1<<i))
		{
			ans=min(ans,Min[a][i]);
			a=jump[a][i];
		}
	if (a==b)
		return ans;
	for (int i=20;~i;i--)
		if (jump[a][i]!=jump[b][i])
		{
			ans=min(ans,min(Min[a][i],Min[b][i]));
			a=jump[a][i],b=jump[b][i];
		}
	ans=min(ans,min(Min[a][0],Min[b][0]));
	return ans;
}

int main()
{
	freopen("Trouble.in","r",stdin);
	freopen("Trouble.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int a,b,fx,fy;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].v);
	sort(e+1,e+1+m,_cmp);
	for (int i=1;i<=m;i++)
	{
		fx=_find(e[i].a),fy=_find(e[i].b);
		if (fx==fy)
			continue;
		fa[fx]=fy;
		_connect(e[i].a,e[i].b,e[i].v);
		_connect(e[i].b,e[i].a,e[i].v);
	}
	for (int i=1;i<=n;i++)
		if (!deep[i])
			dfs(i,0,0);
	scanf("%d",&q);
	for (int i=1;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		if (_find(a)!=_find(b))
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n",getlca(a,b));
	}
	return 0;
}