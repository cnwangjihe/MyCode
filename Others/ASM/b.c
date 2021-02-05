#include <stdio.h>

int ans=0;
char s[1000000];

int main()
{
	gets(s);
	for (;~sscanf(s,"%s");ans++);
	printf("%d\n,ans");
}