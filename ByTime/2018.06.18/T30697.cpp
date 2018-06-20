#include <bits/stdc++.h>

using namespace std;

double a,b;

int main()
{
	scanf("%lf%lf",&a,&b);
	printf("%.15f %.15f\n",a*a*sin(b)*cos(b)/10.0,a*a*cos(b)*cos(b)/20.0);
	return 0;
}