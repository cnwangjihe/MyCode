#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1008;

bool a[MAXN];
int b[MAXN],c[MAXN];
int n;

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(c,0,sizeof c);
		a[0]=1;
		for (int i=0;i<n;i++)
		{
			if (!a[i])
				continue;
			a[i+3]=1;
			b[i+3]=i;
			a[i+5]=1;
			b[i+5]=i;
			a[i+7]=1;
			b[i+7]=i;
		}
		if (!a[n])
		{
			printf("-1\n");
			continue;
		}
		for (int i=n;i;i=b[i])
			c[i-b[i]]++;
		printf("%d %d %d\n",c[3],c[5],c[7]);
	}
	return 0;
}