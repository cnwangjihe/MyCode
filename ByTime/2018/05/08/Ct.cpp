#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;
 
const int MAXN=100009;

int n,Max=0;
int a[MAXN],s1[MAXN],ans[MAXN],pos[2];
bool f;

int main()
{
 	memset(pos,-1,sizeof pos);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]==Max)
			pos[1]=i,f=1;
		if (a[i]>Max)
			Max=a[i],pos[0]=i,pos[1]=-1,f=0;
		s1[a[i]]++; 

		int t=a[i];
		while (s1[t]>9)
			s1[t]=0,s1[--t]++;
		if (s1[0] && i^n)
		{
			printf("NO\n");
			return 0;
		}
	}
	if (!f || s1[0])
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	f=0;
	for (int i=1;i<=n;i++)
	{
		if (i==pos[0])
		{
			int c=0,t=Max;
			while(!s1[t])
				s1[t--]=9;
			s1[t]--;
			for (int j=Max;j;j--)
			{
				s1[j]+=c;
				if (s1[j]>9)
					c=1,ans[j]=0;
				else
					ans[j]=(10-s1[j])%10,c=(s1[j]==0?0:1);
			}
			printf("0.");
			if (ans[Max]==0)
				ans[Max]=9,ans[Max-1]=8,f=1;
			for(int j=1;j<=Max;j++)
				printf("%d",ans[j]);
			putchar('\n');
		}
		else
		if (i==pos[1] && f)
		{
			printf("0.");
			for(int j=0;j<a[i]-1;j++)
				putchar('0');
			printf("2\n");
		}
		else
		{
			printf("0.");
			for(int j=0;j<a[i]-1;j++)
				putchar('0');
			printf("1\n");
		}
	}
	return 0;
}