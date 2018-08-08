#include <bits/stdc++.h>

using namespace std;

int a[12];

int main()
{
	for (int i=1;i<=10;i++)
		a[i]=i*2;
	printf("%d %d\n",*upper_bound(a+1,a+1+10,5),*upper_bound(a+1,a+1+10,4));
	return 0;
}