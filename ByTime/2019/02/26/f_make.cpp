// Date      : 2019-02-26 10:01:41
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

int a[100000];
int sx,sy,ex,ey;

int main()
{
	freopen("f.in","w",stdout);
	srand(time(0));
	int n=8,q=20;
	printf("%d\n",n);
	for (int i=1;i<=n;i++)
		a[i]=rand()%20,printf("%d ",a[i]);
	printf("\n%d\n",q);
	for (int i=0;i<q;i++)
	{
		sx=rand()%n+1,ex=rand()%n+1;
		sy=rand()%(a[sx]+1),ey=rand()%(a[ex]+1);
		printf("%d %d %d %d\n",sx,sy,ex,ey);
	}
	return 0;
}