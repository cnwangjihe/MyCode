#include <bits/stdc++.h>

using namespace std;

int main()
{
	int *a=new int[100];
	printf("%lld\n",sizeof (a));
	for (int i=1;i<10;i++)
		a[i]=i,printf("%d ",a[i]);
}