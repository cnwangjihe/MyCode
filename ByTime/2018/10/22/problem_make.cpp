#include <bits/stdc++.h>

using namespace std;

int f[1000][1000];
int g[100000];

int main()
{
	int x,y,v;
	srand(time(0));
	freopen("problem.in","w",stdout);
	int n=100,m=100,k=1000;
	printf("%d %d %d\n",n,m,k);
	for (int i=1;i<=k;i++)
	{
		do {x=rand()%n+1,y=rand()%m+1;}
		while (f[x][y]);
		f[x][y]=1;
		do {v=rand()%10000+1;}
		while (g[v]);
		g[v]=1;
		printf("%d %d %d %d\n",x,y,rand()%4,v);
	}
	printf("%d\n",rand()%1000+1);
	return 0;
}