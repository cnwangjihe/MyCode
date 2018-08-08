#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 10009,
		  MAXM = MAXN*2;

int _next[MAXM],_head[MAXN],_node[MAXM];
int a[MAXN];
int fp=0,n,q,ans=0;
bool f;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa,int tar,int t,int sum)
{
	sum+=(a[u]==t?1:0);
	if (u==tar)
	{
		ans=sum;
		f=1;
		return ;
	}
	for (int i=_head[u];(~i)&&!f;i=_next[i])
	{
		if (_node[i]==fa)
			continue;
		dfs(_node[i],u,tar,t,sum);
	}
	return ;
}

int main()
{
	freopen("garden.in","r",stdin);
	freopen("garden.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int u,v,t;
	char c[10];
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		_connect(u,v);
		_connect(v,u);
	}
	for (int i=0;i<q;i++)
	{
		scanf("%s",c);
		if (c[0]=='Q')
		{
			f=0;
			scanf("%d%d%d",&u,&v,&t);
			u^=ans,v^=ans,t^=ans;
			dfs(u,0,v,t,0);
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d%d",&u,&t);
			u^=ans,t^=ans;
			a[u]=t;
		}
	}
}