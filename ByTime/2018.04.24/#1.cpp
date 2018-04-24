#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

unsigned long long n,m,ans,asd;

int main()
{
	scanf("%lld",&m);
	for (unsigned long long n=1;n<=m;n++)
	{
		ans=1;
		for (unsigned long long i=0;i<n;i++)
			ans=ans*n;
		int c=0;
		for (asd=ans;asd;asd/=10,c++);
		printf("%d\n",c);
	}
	return 0;
}