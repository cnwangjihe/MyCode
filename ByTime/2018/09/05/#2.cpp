#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

map < int,map< int,map< int,int > > > f3;
map < int,map< int,map< int,bool > > > vis;
int f2[MAXN][MAXN];
int f1[MAXN];
int n,p;
int s[MAXN],e[MAXN];
int ans;

int dfs3(int x,int y,int z)
{
	if (x<0 || y<0 || z<0)
		return 0;
	if (!vis.count(x) || !vis[x].count(y) || !vis[x][y].count(z) || vis[x][y][z]==0)
	{
		vis[x][y][z]=1;
		f3[x][y][z]=(dfs3(x-1,y,z)+dfs3(x,y-1,z)+dfs3(x,y,z-1))%p;
	}
	return f3[x][y][z];
}

inline int dfs2(int x,int y)
{
	if (x<0 || y<0)
		return 0;
	if (f2[x][y]!=-1)
		return f2[x][y];
	return f2[x][y]=(dfs2(x-1,y)+dfs2(x,y-1))%p;
}

inline int dfs1(int x)
{
	if (x<0)
		return 0;
	if (f1[x]!=-1)
		return f1[x];
	return f1[x]=dfs1(x-1)%p;
}

int main()
{
//	freopen("2647.in","r",stdin);
//	freopen("2647.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&n,&p);
		for (int i=1;i<=n;i++)
			scanf("%d",&s[i]);
		for (int i=1;i<=n;i++)
			scanf("%d",&e[i]);
		if (n==1)
		{
			memset(f1,-1,sizeof f1);
			f1[0]=1;
			ans=0;
			for (int i=s[1];i<=s[1];i++)
				if (dfs1(i)!=0)
					ans++;
		}
		if (n==2)
		{
			memset(f2,-1,sizeof f2);
			f2[0][0]=1;
			ans=0;
			for (int i=s[1];i<=e[1];i++)
				for (int j=s[2];j<=e[2];j++)
					if (dfs2(i,j)!=0)
						ans++;

		}
		if (n==3)
		{
			vis.clear();
			f3[0][0][0]=1;
			vis[0][0][0]=1;
			ans=0;
			for (int i=s[1];i<=e[1];i++)
				for (int j=s[2];j<=e[2];j++)
					for (int k=s[3];k<=e[3];k++)
					{
						if (dfs3(i,j,k)!=0)
							ans++;
					//	printf("%d\n",f3[i][j][k]);
					}
		}
		printf("Case %d: %d\n",cn,ans);
	}
	return 0;
}