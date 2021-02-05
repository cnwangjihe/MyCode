#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXN = 300008,
		  INF  = MAXN;

int n;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		for (int i=0;i<=n;i++)
			b[i]=-1,c[i]=-1,d[i]=INF;
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			c[a[i]]=max(c[a[i]],i-b[a[i]]);
			b[a[i]]=i;
		}
		for (int i=1;i<=n;i++)
			c[i]=max(c[i],n-b[i]);
		for (int i=1;i<=n;i++)
			if (~c[i])
				d[c[i]]=min(d[c[i]],i);
		for (int i=1;i<n;i++)
			d[i+1]=min(d[i],d[i+1]);
		for (int i=1;i<=n;i++)
			printf("%d ",d[i]==INF?-1:d[i]);
		printf("\n");
	}
	return 0;
}