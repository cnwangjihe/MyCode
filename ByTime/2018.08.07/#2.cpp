#include <bits/stdc++.h>

using namespace std;

double a,sum;

int main()
{
	while (1)
	{
		sum=0;
		while (scanf("%lf",&a) && a!=0)
			sum+=a;
		printf("%.2lf\n",sum);
	}
	return 0;
}