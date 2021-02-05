#include <stdio.h>

int main()
{
	unsigned char a=0xaa;
	printf("%hx\n%hx\n",-a,(char)-a);
}