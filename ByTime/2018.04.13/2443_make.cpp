#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

int n,t;

int main()
{
	srand(time(0));
	int t=5;
	freopen("2443.in","w",stdout);
	while (t--)
	{
		int n=100000;
		printf("%d\n",n);
		printf("%d %d\n",0,rand()%2?1:-1);
		for (int i=2;i<=n;i++)
			printf("%d %d\n",rand()%(i-1)+1,rand()%2?1:-1);
	}
	return 0;
}