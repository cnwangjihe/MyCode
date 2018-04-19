#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

int a,b,n,ans;

int main()
{
	freopen("2466.in","r",stdin);
	freopen("2466.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		ans=0;
		scanf("%d%d",&a,&b);
		while (a!=b)
		{
			if (a<b)
				swap(a,b);
			a/=2;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}