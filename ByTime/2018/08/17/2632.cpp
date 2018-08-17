#include <bits/stdc++.h>

using namespace std;

int sum,cnt;
int n,a;

int main()
{
	freopen("2632.in","r",stdin);
	freopen("2632.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		sum=cnt=0;
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a);
			cnt+=a&1;
			sum+=a;
		}
		if (cnt<=1)
			printf("%d\n",sum);
		else
		{
			sum/=cnt;
			sum-=(sum&1)^1;
			printf("%d\n",sum);
		}
	}
	return 0;
}