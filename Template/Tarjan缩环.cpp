#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stack>

using namespace std;

const int MAXN = 10005,
		  MAXM = 100005;

stack <int> Stack;
int head[MAXN*2],_next[MAXM*2],node[MAXM*2],v[MAXN*2];
int f[MAXN*2],dfn[MAXN],low[MAXN],bel[MAXN];
bool _in[MAXN];
int tim,n,m,tn,fp=0,ans=0;

void _add(int a,int b)
{
	_next[fp]=head[a];
	node[fp]=b;
	head[a]=fp++;
	return ;
}

void tarjan(int u)
{
	int o;
	dfn[u]=low[u]=++tim;
	Stack.push(u);
	_in[u]=1;
	for (int i=head[u];i!=-1;i=_next[i])
	{
		if (!dfn[node[i]]) 
			tarjan(node[i]),
			low[u]=min(low[u],low[node[i]]);
		else
		if (_in[node[i]])
			low[u]=min(low[u],dfn[node[i]]);
	}
	if (dfn[u]!=low[u]) return ;
	++n;
	do
	{
		o=Stack.top();
		Stack.pop();
		_in[o]=0;
		bel[o]=n;
		v[n]+=v[o];
	}
	while (u!=o);
	return ;
}

void _rebuild()
{
	for (int i=1;i<=tn;i++)
		for (int j=head[i];j!=-1;j=_next[j])
			if (bel[i]!=bel[node[j]]) _add(bel[i],bel[node[j]]);
	return ;
}

int dp(int u)
{
	if(f[u]!=-1) return f[u];
	f[u]=v[u];
	for(int i=head[u];i!=-1;i=_next[i]) f[u]=max(f[u],v[u]+dp(node[i]));
	return f[u];
}

int main()
{
	int x,y;
	memset(f,-1,sizeof f);
	memset(head,-1,sizeof head);
	memset(dfn,0,sizeof dfn);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&v[i]);
	for (int i=0;i<m;i++)
		scanf("%d%d",&x,&y),
		_add(x,y);
	tn=n;tim=0;
	for (int i=1;i<=tn;i++)
		if (!dfn[i]) tarjan(i);
	_rebuild();
	for (int i=tn+1;i<=n;i++) ans=max(ans,dp(i));
	printf("%d\n",ans);
	return 0;
}