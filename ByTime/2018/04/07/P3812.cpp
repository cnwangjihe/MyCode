#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXC = 62;

long long f[MAXC];
long long ans=0,v;
int n;

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%lld",&v);
		for (int j=51;~j;j--)
			if (v&(1ll<<j))
			{
				if (!f[j])
				{
					f[j]=v;
					break;
				}
				v^=f[j];
			}
	}
	for (int i=51;~i;i--)
		if ((ans^f[i])>ans)
			ans^=f[i];
	printf("%lld\n",ans);
	return 0;
}