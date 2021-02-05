#include <stdio.h>

int a=3,b=2;

int main()
{
	int c=0;
	for (int i=0;i<100;i++)
		c+=2;
	a=a+c;
    b++;
    ++a;
    b+=a;
    printf("%d\n",b);
	return 0;
}