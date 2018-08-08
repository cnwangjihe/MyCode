#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int n,cnt=0;
int a[200];

int main()
{
	scanf("%d",&n);
	a[n]=-100;
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,a+n);
	for (int i=0;i<n;i++)
		if (a[i]!=a[i+1]) cnt++;
	printf("%d\n",cnt);
	for (int i=0;i<n;i++)
		if (a[i]==a[i+1])
			continue;
		else
			printf("%d ",a[i]);
	return 0;
}
