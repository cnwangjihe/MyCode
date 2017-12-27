#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 10000007;

bool f[MAXN];
int prime[1000000];
int n,cnt;

int main()
{
	scanf("%d",&n);
	cnt=0;
	memset(f,0,sizeof f); 
	for (int i=2;i<=n;i++)
	{
		if (!f[i]) prime[cnt++]=i;
		for (int j=0;j<cnt && i*prime[j]<=n;j++)
		{
			f[prime[j]*i]=1;
			if (i%prime[j]==0) break;
		}
	}
}