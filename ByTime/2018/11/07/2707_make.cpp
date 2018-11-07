#include <bits/stdc++.h>

using namespace std;

int main()
{
	freopen("2707.in","w",stdout);
	srand(time(0));
	int n=22,k=rand()%n+1;
	printf("%d %d\n",n,k);
	for (int i=0;i<n;i++)
		printf("%d ",rand()%(n*4));
	puts("");
	for (int i=0;i<n;i++)
		printf("%d ",rand()%(n*4));
	puts("");
	for (int i=0;i<n;i++)
		printf("%d ",rand()%(n*4));
	puts("");
	return 0;
}