#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

int k,t1,t2,t3,ans=1,n;
int f[100009],a[100009];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	fill(f,f+n+1,1);
	for (int i=2;i<=n;i++)
		if (a[i]==a[i-1]+1)
			f[i]=f[i-1]+1,ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}