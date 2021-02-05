#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a.h"

const int MAXN = 1000009;

int ans=0,n;
char s[MAXN],t[MAXN];

int main()
{
	gets(s);
	n=strlen(s);
	for (int i=0;i<n;ans++)
	{
		while (i<n && s[i]==' ') i++;
		while (i<n && s[i]!=' ') i++;
	}
	printf("%d\n",ans-(s[n-1]==' '));
	return 0;
}