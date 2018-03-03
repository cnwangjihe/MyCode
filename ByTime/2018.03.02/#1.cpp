#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

bool f[100000001];
int cnt=0,n;

int main()
{
	scanf("%d",&n);
	for (int i=2;i*i<=n;i++)
		if (!f[i])
			for (int j=2;j*i<=n;j++)
				f[i*j]=1;
	for (int i=2;i<=n;i++)
		cnt+=(!f[i]);
	
	printf("%d\n",cnt);
}
