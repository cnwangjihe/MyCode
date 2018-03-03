#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

int n,m;
long long a,b;

long long gcd(long long a,int long long b)
{
	if (a%b==0)
		return b;
	return gcd(b,a%b);
}

int main()
{
	freopen("#2.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
		a=a*10ll+rand()%10;
	for (int i=0;i<m;i++)
		b=b*10ll+rand()%10;
	for (int i=0;i<n;i++)
	{
		gcd(a,b);
	}
	return 0;
}
