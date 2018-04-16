#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1009;

int sum[MAXN][MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]=sum[i-1][j]^sum[i][j-1]^sum[i-1][j-1]^min(i,j);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",sum[i][j]);
		putchar('\n');
	}
	return 0;
	
} 
