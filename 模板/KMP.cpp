#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int ans=0,k,n,m,x;
char s[1000005],t[10005];
int next[10005];

int main()
{
	scanf("%d",&x);
	for (int xx=0;xx<x;xx++)
	{
		scanf("%s",t); scanf("%s",s);
		n=strlen(s); m=strlen(t);
		next[0]=-1;
		k=-1; ans=0;
		
		for (int i=1;i<m;i++)
		{
			while (k>=0 && t[i]!=t[k+1]) k=next[k];
			if (t[i]==t[k+1]) k++;
			next[i]=k;
		}
		
		k=-1;
		
		for (int i=0;i<n;i++)
		{
			while (k>=0 && s[i]!=t[k+1]) k=next[k];
			if (s[i]==t[k+1]) k++;
			if (k==m-1) 
			{
				ans++;
				k=next[k];/*如果要求不能重叠,则 k=-1*/
			}
		}
		
		printf("%d\n",ans);
		
	}
}