#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

int n,m,ttt,p,x,y;
int mp[59][59];

int main()
{
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&m);
		p=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				do {mp[i][j]=getchar();}
					while (mp[i][j]!='#' && mp[i][j]!='.' && mp[i][j]!='S');
				if (mp[i][j]=='S') 
					x=i,y=j,mp[i][j]=0;
				else
					mp[i][j]=mp[i][j]=='#'?1:0;
			}
		for (int i=1;i<=n;i++)
			p+=mp[i][y];
		for (int i=1;i<=m;i++)
			p+=mp[x][i];
		if (p)
			printf("-1\n");
		else
			printf("%d\n",n+m-2);
	}
	return 0;
}
