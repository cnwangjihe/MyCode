#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

char c[10000];
int n,t,m=0;

int main()
{
	srand(time(0));
	scanf("%d",&n);
	for (int i='a';i<='z';i++)
		c[m++]=i;
	for (int i='0';i<='9';i++)
		c[m++]=i;
	for (int i='A';i<='Z';i++)
		c[m++]=i;
	c[m++]=';';
	c[m++]=':';
	c[m++]='.';
	c[m++]='*';
	c[m++]='#';
	c[m++]=',';
	t=(rand()*rand())%100000+10000;
	for (int i=0;i<t;i++)
		swap(c[(rand()*rand())%m],c[(rand()*rand())%m]);
	for (int i=0;i<n;i++)
		putchar(c[(rand()*rand())%m]);
	putchar('\n');
	return 0;
}