#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 3010;

int _next[MAXN*MAXN*2],node[MAXN*MAXN*2],head[MAXN],compare[MAXN];
bool f[MAXN];
int a,b,n,m,k,fp,ans;

void _connect(int a,int b)
{
	_next[fp]=head[a];
	node[fp]=b;
	head[a]=fp;
	fp++;
}

bool Hungary(int root)
{
	f[root]=1;
	for (int i=head[root];i!=-1;i=_next[i])
	{
		if (f[node[i]]) continue;
		f[node[i]]=1;
		if (compare[node[i]]==-1 || Hungary(compare[node[i]]))
		{
			compare[node[i]]=root;
			return 1;
		}
	}
	return 0;
}

int main()
{
//	while (1)
	{
		ans=fp=0;
		memset(head,-1,sizeof head);
		memset(_next,-1,sizeof _next);
		memset(compare,-1,sizeof compare);
		scanf("%d%d",&n,&m);
		scanf("%d",&k);
		if (k==0) return 0;
		for (int i=0;i<k;i++)
		{
			scanf("%d%d",&a,&b);
			if (b>m) continue;
			_connect(a,b+n);
			_connect(b+n,a);
		}
		for (int i=1;i<=n;i++)
		{
			memset(f,0,sizeof f);
			if (Hungary(i)) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
