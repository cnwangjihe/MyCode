#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 11,
		  MAXM = MAXN*MAXN*8;

int head[MAXN],_next[MAXM],node[MAXM];
int n,m,fp=0,ans;
bool mp[MAXN][MAXN],f[MAXN*2];
int compare[MAXN*2],a[MAXN*2];

void _add(int x,int y)
{
	_next[fp]=head[x];
	node[fp]=y;
	head[x]=fp++;
	return ;
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
	int x,y,sum;
	while (scanf("%d%d",&n,&m)==2)
	{
		ans=0;
		memset(mp,0,sizeof mp);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			mp[x][y]=1;
		}
		if (n==1 && mp[1][1])
		{
			printf("1\n");
			continue;
		}
		if (n<=1)
		{
			printf("0\n");
			continue;
		}
		for (int i=1;i<=n;i++)
			a[i]=i;
		do
		{
			fp=0;
			memset(compare,-1,sizeof compare);
			memset(head,-1,sizeof head);
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					if (!mp[i][a[j]] && !mp[i][a[j%n+1]])
						_add(i,j+n),_add(j+n,i);
			sum=0;
			for (int i=1;i<=n;i++)
			{
				memset(f,0,sizeof f);
				if (Hungary(i)) sum++;
			}
			ans=max(ans,sum);
		}while(next_permutation(a+2,a+n+1));
		printf("%d\n",n-ans);
	}
}
