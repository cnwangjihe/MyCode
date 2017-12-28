#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100009;

bool f[MAXN];
vector<int> line[MAXN];
bool ans,flag;
int n,m,cnt=0;

bool pd(int x,int y)
{
	if (!(f[x]^f[y])) return x<y;
	return f[x];
}

void solve(int l,int r,int k)
{
	if (!ans || l>=r) return ;
	while (l<=r && k>=line[l].size()) l++;
	int tmp=l;
	for (int i=l+1;i<=r;i++)
	{
		if (k>=line[i].size()) 
		{
			ans=0;
			return ;
		}
		if ( pd(line[i][k],line[i-1][k]) )
		{
			for (int j=i-1;j>=l;j--)
			{
				if ( pd(line[j][k],line[j+1][k]) ) break;
				if ( !f[ line[j][k] ] ) flag=1;
				f[ line[j][k] ]=1;
				if ( pd(line[j+1][k],line[j][k]) )
				{
					ans=0;
					return ;
				}
			}
		}
	}
	for (int i=l;i<=r;i++)
	{
		if (line[i][k]!=line[tmp][k])
		{
			solve(tmp,i-1,k+1);
			if (!ans) return ;
			tmp=i;
		}
		if (i==r && line[i][k]==line[tmp][k])
		{
			solve(tmp,i,k+1);
			if (!ans) return ;
		}
	}
	return ;
}

int main()
{
//	freopen("2333.in","r",stdin);
//	freopen("2333.out","w",stdout);
	int len,x,sum=0;
	scanf("%d%d",&n,&m);
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&len);
		for (int j=1;j<=len;j++)
		{
			scanf("%d",&x);
			line[i].push_back(x);
		}
	}
	ans=1;
	do
	{
		flag=0;
		solve(1,n,0);
	}while (flag && ans);
	if (!ans)
	{
		printf("No\n");
		return 0;
	}
	for (int i=1;i<=m;i++)
		if (f[i]) sum++;
	printf("Yes\n%d\n",sum);
	for (int i=1;i<=m;i++)
		if (f[i]) printf("%d ",i);
	return 0;
}
