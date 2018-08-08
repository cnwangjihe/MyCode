#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

using namespace std;

int n,Max;
int a[1000010],c[10010];

int main()
{
	int tmp;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		a[tmp]++;
		Max=max(Max,tmp);
	}
	for (int i=1;i<=Max;i++)
	{
		tmp=0;
		for (int j=1;i*j<=Max;j++)
			tmp+=a[i*j];
		for (int j=1;j<=tmp;j++)
			c[j]=max(c[j],i);
	}
	for (int i=1;i<=n;i++)
		printf("%d\n",c[i]);
	return 0;
}
