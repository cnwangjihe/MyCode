#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	int n=80;
	freopen("P3967.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%d ",rand()%5001);
		printf("\n");
	}
	fclose(stdout);
	return 0;
}