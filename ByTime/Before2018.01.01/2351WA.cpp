#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

int c[304],f[304];
char ch[304],s;
int fp=1,n,ans=0;

bool _check(char c) {return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9');}

int main()
{
	freopen("2351.in","r",stdin);
	freopen("2351.out","w"stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		do {s=getchar();}
			while (!_check(s));
		f[s]=(!f[s])?fp++:f[s];
		c[f[s]]++;
		ch[f[s]]=s;
	}
	for (int i=1;i<fp;i++)
		if (c[i]&1) ans++;
	printf("%d\n",max(1,ans));
	for (int i=1;i<fp;i++)
	{
		if (c[i]&1) continue;
		for (int j=0;j*2<c[i];j++) 
			putchar(ch[i]);
	}
	for (int i=1;i<fp;i++)
	{
		if (!(c[i]&1)) continue;
		for (int j=0;j<c[i];j++) 
			putchar(ch[i]);
		c[i]=0;
		break;
	}
	for (int i=1;i<fp;i++)
	{
		if (c[i]&1) continue;
		for (int j=0;j*2<c[i];j++) 
			putchar(ch[i]);
	}
	putchar(' ');
	for (int i=1;i<fp;i++)
	{
		if (!(c[i]&1)) continue;
		for (int j=0;j<c[i];j++) 
			putchar(ch[i]);
		putchar(' ');
	}
	return 0;
}
