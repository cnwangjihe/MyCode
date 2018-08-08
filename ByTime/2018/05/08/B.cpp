#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 10009;

int n;
long long a[MAXN];

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%lld",&a[i]);
	for (int i=n-1;~i;i--)
		printf("%lld ",a[i]);
	return 0;
}