#include <bits/stdc++.h>

using namespace std;

int n = 100000;

int main()
{
	srand(time(0));
	freopen("2703.in","w",stdout);
	printf("%d\n",n);
	for (int i=1;i<=n;i++)
		printf("%d ",rand()%n+1);
	return 0;
}