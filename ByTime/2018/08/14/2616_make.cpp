#include <bits/stdc++.h>

int main()
{
	freopen("2616.in","w",stdout);
	srand(time(0));
	int n=30000,m=rand()%9900+100,mod=rand()%9990+2,w1=rand()%mod;
	int step=rand()%(mod-1)+1;
	printf("%d %d %d %d %d\n",n,m,w1,step,mod);
	for (int i=0;i<n;i++)
		printf("%d ",rand()%mod);
	return 0;
}