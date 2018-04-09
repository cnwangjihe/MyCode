#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

int k,t1,t2,t3,f=0;

int main()
{
	scanf("%d",&k);
	for (int i=10000;i<=30000;i++)
	{
		t1=i/100;
		t2=(i/10)%(1000);
		t3=i%1000;
		if (t1%k+t2%k+t3%k==0)
			printf("%d\n",i),f=1;
	}
	if (!f)
		printf("No\n");
	return 0;
}