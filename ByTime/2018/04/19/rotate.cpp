#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 1009;

char mp[MAXN][MAXN],tmp[MAXN][MAXN];
int n,q,x,y,z;

int main()
{
	freopen("rotate.in","r",stdin);
	freopen("rotate.out","w",stdout);
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			do {mp[i][j]=getchar();}
				while (mp[i][j]<'a' || mp[i][j]>'z');
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		for (int i=0;i<z;i++)
			for (int j=0;j<z;j++)
				tmp[z-j-1][i]=mp[x+i][y+j];
		for (int i=0;i<z;i++)
			for (int j=0;j<z;j++)
				mp[i+x][j+y]=tmp[i][j];
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			putchar(mp[i][j]);
		putchar('\n');
	}
	return 0;
}