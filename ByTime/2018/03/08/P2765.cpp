#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 109;

int top[MAXN][MAXN],fp[MAXN];
bool f[MAXN*MAXN*MAXN];
int n,ans;

int main()
{
	memset(top,-1,sizeof top);
	scanf("%d",&n);
	for (int i=1;i*i<=100*100*100;i++)
		f[i*i]=1;
	bool flag=1;
	for (ans=1;flag;ans++)
	{
		flag=0;
		for (int i=0;i<n;i++)
			if (!fp[i] || f[top[i][fp[i]]+ans])
			{
			//	cerr << i << ':' << ans << ':' << top[i] << endl;
				
				top[i][++fp[i]]=ans;
				flag=1;
				break;
			}
	//	if (ans>=10000)
	//		return printf("F**k\n")&0;
	}
	printf("%d\n",ans-2);
	for (int i=0;i<n;i++)
	{
		for (int j=1;j<=fp[i];j++)
			printf("%d ",top[i][j]);
		putchar('\n');
	}
	return 0;
}
