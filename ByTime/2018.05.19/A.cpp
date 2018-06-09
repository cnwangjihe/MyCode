#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

using namespace std;

int n;
long long v,sum=0;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&v),sum+=v;
	printf("%s\n",(sum%2ll)?"Alice":"Bob");	 
	return 0;
}