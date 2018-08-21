#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int _head[MAXN],_next[MAXN],_node[MAXN];
int ans[MAXN],b[MAXN],t[MAXN],p[MAXN];
bool fg[MAXN];
int c[MAXN];
int fp=0,n,m=0,cnt=0;

bool _cmp(int a,int b) {return t[a]<t[b];}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
	int v;
	ans[t[u]]=min(ans[t[u]],cnt);
	if (c[t[u]]==0)
		cnt++;
	c[t[u]]++;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		dfs(v);
	}
	c[t[u]]--;
	if (c[t[u]]==0)
		cnt--;
	return ;
}

int main()
{
	freopen("2644.in","r",stdin);
	freopen("2644.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&t[i]),b[i]=t[i],p[i]=i;
	sort(p+1,p+1+n,_cmp);
	for (int i=1;i<=n;i++)
	{
		m++;
		ans[m]=n;
		b[m]=t[p[i]];
		while (i+1<=n && t[p[i]]==t[p[i+1]])
			t[p[i]]=m,i++;
		t[p[i]]=m;
	}
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		fg[y]=1;
		_connect(x,y);
	}
	for (int i=1;i<=n;i++)
		if (!fg[i])
			dfs(i);
	for (int i=1;i<=m;i++)
		printf("%d %d\n",b[i],ans[i]+1);
	return 0;
}