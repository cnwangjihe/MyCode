#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

long long n;
double ans;

int main()
{
	scanf("%lld",&n);
	for (long long i=1;i*i<=n;i++)
	{
		ans+=sqrt((double)n/(double)i);
	}
	printf("%.6f",ans);
	return 0;
}