#include <stdio.h>

using namespace std;

const int MAXN = 1008;

int cnt,p,n,k;
int a[MAXN];

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&k);
		cnt=p=0;
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			p=a[p]>a[i]?i:p;
		}
		for (int i=0;i<n;i++)
		{
			if (i==p)
				continue;
			cnt+=(k-a[i])/a[p];
		}
		printf("%d\n",cnt);
	}
	return 0;
}