#include <bits/stdc++.h>

using namespace std;

int main()
{
	freopen("walk.in","w",stdout);
	srand(time(0));
	int n=20,m=20;
	printf("%d %d %d\n",n,m,rand()%100000001);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			printf("%d ",rand()%1000000001);
		putchar('\n');
	}
}