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
	freopen("bag.in","w",stdout);
	srand(time(0));
	int n=20,s=rand()%50000000;
	printf("%d %d\n",n,s);
	for (int i=0;i<n;i++)
	{
		printf("%d ",rand()%s+1);
	}
	printf("\n");
	return 0;
}