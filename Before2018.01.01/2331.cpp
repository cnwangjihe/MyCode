#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

int a[100009];
int n,cnt=0,ans=0,sum;

int main()
{
//	freopen("2331.in","r",stdin);
//	freopen("2331.out","w",stdout);
	scanf("%d",&n);
	for (int i=n;i;cnt++,i/=10);
	for (int i=n-cnt*9;i<=n;i++)
	{
		sum=i;
		for (int j=i;j;sum+=j%10,j/=10);
		if (sum==n) a[ans++]=i;
	}
	printf("%d\n",ans);
	for (int i=0;i<ans;i++) printf("%d\n",a[i]);
	return 0;
}

