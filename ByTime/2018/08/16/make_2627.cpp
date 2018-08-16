#include <bits/stdc++.h>

using namespace std;

int u,n,m;

int main()
{
	srand(time(0));
	freopen("2627.in","w",stdout);
	n=12,m=rand()%12+1;
	printf("%d %d\n",n,m);
	for (int i=2;i<=n;i++)
		printf("%d %d\n",i,rand()%(i-1)+1);
	for (int i=0;i<m;i++)
	{
		u=rand()%(n-1)+2;
		printf("%d %d\n",u,rand()%(u-1)+1);
	}
	return 0;
}