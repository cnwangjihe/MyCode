#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cstring>
#include <math.h>
#include <cmath>

using namespace std;

const int MAXV = 10000006,
          MAXN = 406;

int head[MAXN],v[MAXN],node[MAXN],next[MAXN];
bool f[MAXN];
int n,m,x,y,z,Min,ans=0,fp=0;

bool dfs(int k)
{
	int xx,xxx;
	if (k==n) {ans+=Min;return 1;}
	f[k]=1;
	for (int i=head[k];i!=-1;i=next[i])
	{
		if (v[i]==0 || f[node[i]]) continue;
		int mx=Min;
		Min=min(Min,v[i]);
		if (dfs(node[i]))
		{
			v[i]-=Min;
			v[i^1]+=Min;
			return 1;
		}
		Min=mx;
	}
	return 0;
}

void _insert(int x,int y,int z)
{
	node[fp]=y;
	next[fp]=head[x];
	head[x]=fp;
	v[fp]=z;
	fp++;
}

int main()
{
	while (~scanf("%d%d",&m,&n))
	{
		ans=0;fp=0;
		memset(head,-1,sizeof head);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			_insert(x,y,z);
			_insert(y,x,0);
		}
		do
		{
			memset(f,0,sizeof f);
			Min=MAXV;
		}while (dfs(1));
		printf("%d\n",ans);
	}
	return 0;
}