#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
	freopen("gwent.in","w",stdout);
	srand(time(0));
	int n=200000;
	printf("%d\n",n);
	for (int i=0;i<n;i++)
	{
		printf("%d %d\n",rand()%10000001,rand()%10000001);
	}
	int m=1000000;
	printf("%d\n",m);
	for (int i=0;i<m;i++)
	{
		printf("%d %d\n",rand()%n+1,rand()%n+1);
	}
	return 0;
}