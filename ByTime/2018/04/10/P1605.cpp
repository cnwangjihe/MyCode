#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

int mp[10][10],f[10][10];
int xx1,xx2,yy1,yy2,x,y,n,m,k;

int dfs(int x,int y)
{
	if (x<=0 || x>n || y<=0 || y>m || f[x][y] || mp[x][y])
		return 0;
	if (x==xx2 && y==yy2)
		return 1;
	f[x][y]=1;
	int tmp=dfs(x+1,y)+dfs(x,y+1)+dfs(x-1,y)+dfs(x,y-1);
	f[x][y]=0;
	return tmp;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	scanf("%d%d%d%d",&xx1,&yy1,&xx2,&yy2);
	for (int i=0;i<k;i++)
	{
		scanf("%d%d",&x,&y);
		mp[x][y]=1;
	}
	printf("%d\n",dfs(xx1,yy1));
	return 0;
}