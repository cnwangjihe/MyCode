#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 300009;

int p[MAXN],f[MAXN];
int n,sum=0,pos;

int main()
{
//	freopen("2332.in","r",stdin);
//	freopen("2332.out","w",stdout);
	scanf("%d",&n);
	pos=n;
	for(int i=0;i<n;i++) scanf("%d",&p[i]);
	printf("1 ");
	for(int i=0;i<n;i++)
	{
		f[p[i]]=1; sum++;
		for (;f[pos];sum--,pos--);
		printf("%d ",sum+1);
	}
	return 0;
}
