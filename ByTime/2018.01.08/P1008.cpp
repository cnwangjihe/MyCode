#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int a[15];
bool f;

int main()
{
	for (int i=100;i<=400;i++)
	{
		a[1]=i%10;
		a[2]=i%100/10;
		a[3]=i/100;
		a[4]=2*i%10;
		a[5]=2*i%100/10;
		a[6]=2*i/100;
		a[7]=3*i%10;
		a[8]=3*i%100/10;
		a[9]=3*i/100;
		sort(a+1,a+10);
		f=1;
		for (int j=1;j<=9 && f;j++)
			if (a[j]!=j) f=0;
		if (!f) continue;
		printf("%d %d %d\n",i,i*2,i*3);
	}
	return 0;
}
