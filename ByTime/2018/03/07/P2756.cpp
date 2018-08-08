#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 409;

int _next[MAXN*MAXN*2],_node[MAXN*MAXN*2],_head[MAXN],compare[MAXN];
int n,m,a,b;
int fp=0,ans=0;
bool f[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

bool Hungary(int root)
{
	int v;
	f[root]=1;
	for (int i=_head[root];~i;i=_next[i])
	{
		v=_node[i];
		if (f[v]) continue;
		f[v]=1;
		if (compare[v]==-1 || Hungary(compare[v]))
		{
			compare[v]=root;
			return 1;
		}
	}
	return 0;
}

int main()
{
	memset(compare,-1,sizeof compare);
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	while (scanf("%d%d",&a,&b)==2 && (~a) && (~b))
	{
		_connect(a,b+n);
		_connect(b+n,a);
	}
	for (int i=1;i<=n;i++)
	{
		memset(f,0,sizeof f);
		if (Hungary(i)) ans++;
	}
	if (!ans)
		return printf("No Solution!\n")&0;
	printf("%d\n",ans);
	for (int i=n+1;i<=n+m;i++)
		if (~compare[i])
			printf("%d %d\n",compare[i],i-n);
	return 0;
}
