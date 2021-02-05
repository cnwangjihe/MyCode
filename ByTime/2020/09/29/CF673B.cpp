#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 100008;

bool flag;
int cnt,n,T;
bool c[MAXN];
int a[MAXN];

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		cnt=0;
		memset(c,0,sizeof c);
		scanf("%d%d",&n,&T);
		flag=(T%2==0);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			c[i]=(a[i]<=T/2);
			cnt+=(flag && a[i]==T/2);
		}
		int tmp=0;
		for (int i=0;i<n && flag;i++)
		{
			if (a[i]!=T/2)
				continue;
			c[i]=(++tmp<=cnt/2);
		}
		for (int i=0;i<n;i++)
			printf("%d ",c[i]);
		printf("\n");
	}
	return 0;
}