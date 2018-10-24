#include <bits/stdc++.h>

using namespace std;

int n,m;

int main()
{
	freopen("takeaway.in","w",stdout);
	srand(time(0));
	int n=3000,m=70000;
	printf("%d %d\n",n,m);
	for (int i=1;i<=m;i++)
		printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%100000000+1);
	for (int i=1;i<=n;i++)
	{
		printf("%d ",n-1);
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			printf("%d ",j);
		}
		puts("");
	}
	return 0;
}