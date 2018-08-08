#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
	freopen("P1084.in","w",stdout);
	srand(time(0));
	int n=6;
	printf("%d\n",n);
	for (int i=2;i<=n;i++)
		printf("%d %d %d\n",i,rand()%(i-1)+1,rand()%100);
	int m=rand()%(n-3)+1+3;
	printf("%d\n",m);
	for (int i=0;i<m;i++)
	{
		printf("%d ",rand()%(n-1)+2);
	}
	return 0;
}