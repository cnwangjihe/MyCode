#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

int a[3],b,c;

int gcd(int a,int b)
{
	return a%b==0?b:gcd(b,a%b);
}

int main()
{
	scanf("%d%d%d",&a[0],&a[1],&a[2]);
	sort(a,a+3);
	b=a[0];
	c=a[2];
	printf("%d/%d\n",b/gcd(b,c),c/gcd(b,c));
	return 0;
}