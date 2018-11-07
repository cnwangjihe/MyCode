#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500009,
		  MAXM = MAXN*2;

int _head[MAXN],_next[MAXM],_node[MAXM];
int val[MAXN],cnt[MAXN];
long long f[MAXN];
int n,m,fp=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	priority_queue< pair<long long,int> , vector< pair<long long,int> >, less< pair<long long,int> > > a;
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
		a.push(make_pair(f[v]-cnt[v],v));
	}
	cnt[u]=0;
	while (!a.empty())
	{
		v=a.top().second;
		a.pop();
		f[u]=max(f[u],1ll+cnt[u]+f[v]);
		cnt[u]+=cnt[v]+2;
	}
	f[u]=max(f[u],1ll*cnt[u]);
	if (u==1)
		f[u]=max(f[u],1ll*cnt[u]+val[u]);
	else
		f[u]=max(f[u],1ll*val[u]);
//	cerr << "## " << u << " : " << f[u] << " " << cnt[u] << endl;
	return ;
}

int main()
{
//	freopen("a.in","r",stdin);
	memset(_head,-1,sizeof _head);
	int a,b;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
	}
	dfs(1,0);
	printf("%lld\n",f[1]);
	return 0;
}