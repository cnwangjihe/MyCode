#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int num[10000],sco[10000];
int n,m,a,b=0;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d%d",&num[i],&sco[i]);
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			if(sco[i]<sco[j])
			{
				swap(sco[i],sco[j]);
				swap(num[i],num[j]);
			}
			else if(sco[i]==sco[j])
			{
				if(num[j]<num[i])
					swap(num[j],num[i]);
			}
		}
	m=floor(1.5*m);
	a=sco[m-1];
	for(int i=0;i<n;i++)
	{
		if(sco[i]>=a)
			b++;
		else
			break;
	}
	printf("%d %d\n",a,b);
	for(int i=0;i<b;i++)
		printf("%d %d\n",num[i],sco[i]);
	return 0;
} 
