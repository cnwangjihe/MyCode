#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

int a[100];
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	nth_element(a+1,a+m,a+n+1);
	for (int i=1;i<=n;i++)
		printf("%d ",a[i]);
	return 0;
}