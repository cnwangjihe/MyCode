/*
state:Accepted
submit:http://acm.zju.edu.cn/
RunID:4152356
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 10009,
		  MAXC = 109;

double f[MAXN][MAXC];
int c,n,m;

int main()
{
	while (scanf("%d",&c) && c)
	{
		scanf("%d%d",&n,&m);
		if(!n && !m)
		{
			printf("1.000\n");
			continue;
		}
		if(m>c || m>n || ((m+n)&1))
		{
			printf("0.000\n");
			continue;
		}
		if (n>10000)
			n=10000+(n&1);
		memset(f,0,sizeof f);
		f[1][1]=1;
		for (int i=2;i<=n;i++)
			for (int j=0;j<=min(i,c);j++)
			{
				if((i+j)&1)
				{
					f[i][j]=0;
					continue;
				}
				if(j>0) 
					f[i][j]+=f[i-1][j-1]*double(c-j+1)/double(c);
				if(j+1<i)
					f[i][j]+=f[i-1][j+1]*double(j+1)/double(c);
			}
		printf("%.3f\n",f[n][m]);
	}
	return 0;
}
