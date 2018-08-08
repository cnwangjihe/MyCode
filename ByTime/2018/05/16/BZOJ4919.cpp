#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

using namespace std;

const int MAXN = 200009;

multiset<int> s[MAXN];
int _head[MAXN],_next[MAXN],_node[MAXN];
int tp=0,fp=0,n;
int num[MAXN],val[MAXN];
int siz[MAXN],son[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
//	cerr << u << endl;
	int v;
	siz[u]=1;
	son[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		dfs(v);
		siz[u]+=siz[v];
		if (siz[v]>siz[son[u]])
			son[u]=v;
	}
	if (siz[u]==1)
		num[u]=tp++;
	else
		num[u]=num[son[u]];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==son[u])
			continue;
	//	if (num[v]==-1)
	//		continue;
		for (multiset<int>::iterator j=s[num[v]].begin();j!=s[num[v]].end();j++)
			s[num[u]].insert(*j);
	//	s[num[v]].~multiset();
	//	num[v]=-1;
	}
	multiset<int>::iterator p=s[num[u]].lower_bound(val[u]);
	if (p!=s[num[u]].end())
		s[num[u]].erase(p);
	s[num[u]].insert(val[u]);
	return ;
}

int main()
{
	int v;
	memset(_head,-1,sizeof _head);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&val[i],&v);
		if (v!=0)
			_connect(v,i);
	}
	dfs(1);
	printf("%d\n",s[num[1]].size());
	return 0;
}