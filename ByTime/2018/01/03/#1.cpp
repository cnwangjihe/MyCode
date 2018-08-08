#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 100009;

int n;
int a[MAXN];

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,a+n);
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	return 0;
}
