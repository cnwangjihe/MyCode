// Date      : 2018-12-26 19:50:53
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

int rnd(){return ((rand()<<15)+rand())%1000000001;}

int main()
{
	srand(time(0));
//	freopen("2738_make.in","r",stdin);
	freopen("2738.in","w",stdout);
	int n,m;
	do {n=rand()%100+1,m=rand()%100+1;}
		while (n==1 && m==1);
	printf("%d %d %d %d %d\n",n,m,rnd()%n+1,rnd()%m+1,rnd()%1000000/2*2);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			printf("%d ",rnd());
		putchar('\n');
	}
	return 0;
}