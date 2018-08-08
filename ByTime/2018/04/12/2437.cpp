#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int f[1000009];

int main()
{
	freopen("2437.in","r",stdin);
	freopen("2437.out","w",stdout);
	memset(f,-1,sizeof f);
	scanf("%d",&n);
	f[0]=0;
	for (int i=0;i+3<=n;i++)
		if (~f[i])
			f[i+3]=max(f[i+3],f[i]+7);
	for (int i=0;i+2<=n;i++)
		if (~f[i])
			f[i+2]=max(f[i+2],f[i]+1);
	for (int i=0;i+4<=n;i++)
		if (~f[i])
			f[i+4]=max(f[i+4],f[i]+4);
	for (int i=0;i+6<=n;i++)
		if (~f[i])
			f[i+6]=max(f[i+6],f[i]+9);
	printf("%d\n",f[n]);
	return 0;
}