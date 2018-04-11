#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

int n,cnt=0;

int main()
{
	for (;;)
	{
		cnt=0;
		scanf("%d",&n);
		for (long long i=0;i<(1ll<<(long long)n);i++)
			if ((i^(4ll*i))==((2ll*i)^(7ll*i)))
				printf("%lld ",i),cnt++;
		printf("\n%d\n",cnt);
	}
	return 0;
}