#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

int t,n;

int main()
{
//	freopen(".in","r",stdin);
	freopen("sam.in","w",stdout);
	t=1;
	n=100000;
	srand(time(0));
	printf("%d\n",t);
	for (int i=0;i<t;i++)
	{
		for (int j=0;j<n;j++)
			putchar(rand()%8+'A');
		putchar('\n');
	}
	return 0;
}