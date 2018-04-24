#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

int n,a;
double x,y;
int cnt1=0,cnt2=0;

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%lf%lf",&x,&y);
		a=x*10+y*10;
		if (a%10==0)
			cnt1++;
		else
			cnt2++;
	}
	printf("%s\n",cnt1==cnt2?"O_O":(cnt1>cnt2?"Lose":"Win"));
	return 0;
}