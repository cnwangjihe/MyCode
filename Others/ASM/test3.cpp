#include <stdio.h>

using namespace std;


	int a[10]={[2]=3,[3]=4};

int main()
{
	for (int i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}