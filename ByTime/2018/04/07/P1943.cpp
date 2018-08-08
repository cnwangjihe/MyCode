#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;

int n;
double ans;

int main()
{
	scanf("%d",&n);
	if (n>80000000)
		printf("%.8lf\n",log((double)n+1.0)+0.57721566490153286060651209);
	else
	{
		for (int i=1;i<=n;i++)
			ans+=(double)1.0/(double)i;
		printf("%.8lf\n",ans);
	}
	return 0;
}