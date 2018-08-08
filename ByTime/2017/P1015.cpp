#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

using namespace std;

char s[405];
int a[405],top;

bool pd()
{
	int t=top/2;
	for (int i=0;i<=t;i++)
		if (a[i]!=a[top-i]) return true;
	return false;
}
int main()
{
	int n,ans=0;
	scanf("%d%s",&n,s);
	top=strlen(s)-1;
	for (int i=0;i<=top;i++) 
		if (s[i]>='0'&&s[i]<='9') a[top-i]=s[i]-'0';
			else a[top-i]=s[i]-55;
	while (pd())
	{
		if (ans>30)
		{
			printf("Impossible!\n");
			return 0;
		}
		for (int i=0;i<=top;i++) 
			if (top-i>=i) a[i]+=a[top-i];
				else a[i]=a[top-i];  
		for (int i=0;i<=top;i++) 
			if (a[i]>=n) a[i+1]++,a[i]-=n;
		if (a[top+1]) top++;
		ans++;
	}
	printf("STEP=%d\n",ans);
	return 0;
}
