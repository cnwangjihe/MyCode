#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	long long a=1,ans=1,k;
	scanf("%d%d",&a,&k);
	a++;
	for (int i=1;i<=k;i++)
		ans=ans*a;
	printf("%lld\n",ans);
}