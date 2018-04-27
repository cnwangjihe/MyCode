#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

int n,a,b,t;
long long sum=0;

int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for (int i=1;i<=n;i++)
		scanf("%d",&t),sum=sum+(long long)t;
	printf("%lld\n",sum);
}