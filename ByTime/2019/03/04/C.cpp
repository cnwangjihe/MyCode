// Date      : 2019-03-04 10:43:06
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 200009;

stack <int> Stack;
int _head[MAXN*2],_next[MAXM*2],_node[MAXM*2];
int dfn[MAXN],low[MAXN],bel[MAXN];
int d[MAXN*2],f[MAXN*2];
bool _in[MAXN*2];
int tim,n,m,ty,tn,fp=0;
int ans2,ans;
queue<int> q;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void tarjan(int u)
{
	int o,v;
	dfn[u]=low[u]=++tim;
	Stack.push(u);
	_in[u]=1;
	for (int i=_head[u];i!=-1;i=_next[i])
	{
		v=_node[i];
		if (!dfn[v]) 
			tarjan(v),
			low[u]=min(low[u],low[v]);
		else if (_in[v])
			low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]!=low[u])
		return ;
	int cnt=0;
	++n;
	do
	{
		o=Stack.top();
		Stack.pop();
		_in[o]=0;
		bel[o]=n;
		cnt++;
	} while (u!=o);
	ans2=cnt*ans2/__gcd(cnt,ans2);
	return ;
}


void Rebuild()
{
	for (int i=1;i<=tn;i++)
		for (int j=_head[i];~j;j=_next[j])
			if (bel[i]!=bel[_node[j]])
			{
				_connect(bel[i],bel[_node[j]]);
				d[bel[_node[j]]]++;
			}
	return ;
}

void Calc()
{
	ans=0;
	for (int u=tn+1;u<=n;u++)
		if (!d[u])
			q.push(u);
	int u,v;
	while (!q.empty())
	{
		u=q.front(),q.pop();
		ans=max(ans,f[u]);
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			f[v]=max(f[v],f[u]+1);
			if (!--d[v])
				q.push(v);
		}
	}
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d",&n,&m,&ty);
	tn=n;tim=0;
	int x,y;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
	}
	ans2=1;
	for (int i=1;i<=n;i++)
		if (!dfn[i])
			tarjan(i);
	if (ty!=1)
		return printf("%d\n",ans2),0;
	ans=ans2;
	Rebuild(),Calc();
	printf("%d %d\n",ans,ans2);
	return 0;
}
