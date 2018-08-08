#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

int p,a,b,c,d,n;
double ans,price[1000005];

inline double calc(int k)
{
	return (double)p*(sin(a*k+b)+cos(c*k+d)+2);
}

int main()
{
	scanf("%d%d%d%d%d%d",&p,&a,&b,&c,&d,&n);
	for (int i=1;i<=n;i++)
		price[i]=calc(i);
	double mx=price[1];
	for (int i=2;i<=n;i++)
	{
		ans=max(ans,mx-price[i]);
		mx=max(mx,price[i]);
	}
	printf("%.6lf\n",ans);
	return 0;
}
