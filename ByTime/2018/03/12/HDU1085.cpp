#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100006,
		  coin[3] = {1,2,5};

int value[MAXN],temp[MAXN],num[3];

int main()
{
	while (scanf("%d%d%d",&num[0],&num[1],&num[2]) && num[0]+num[1]+num[2])
	{
		int max=num[0]+2*num[1]+5*num[2];
		memset(temp,0,sizeof temp);
		memset(value,0,sizeof value);
		for (int i=0;i<=num[0];i++)
			value[i]=1;
		for (int i=1;i<3;i++)
		{
			for (int j=0;j<=max;j++)
				for (int k=0;k+j<=max && k/coin[i]<=num[i];k+=coin[i])
					temp[k+j]+=value[j];
			for (int j=0;j<=max;j++)
				value[j]=temp[j],temp[j]=0;
		}
		for (int i=0;i<=max+1;i++)
			if (!value[i]) 
			{
				printf("%d\n",i);
				break;
			}
	}
	return 0;  
}