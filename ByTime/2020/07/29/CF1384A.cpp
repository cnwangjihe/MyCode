#include <bits/stdc++.h>

using namespace std;

const int MAXM = 50,
		  MAXN = 105;

int n;
int a[MAXN];

void Print(long long a)
{
	for (int i=0;i<MAXM;i++)
		printf("%c",(a&(1ll<<i))?'a':'b');
	printf("\n");
	return ;
}

int main()
{
	int tt;
	long long base,now,tmp;
	scanf("%d",&tt);
	for (;tt--;)
	{
		scanf("%d",&n);
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		base=(1ll<<MAXM)-1;
		now=base;
		Print(now);
		for (int i=0;i<n;i++)
		{
			tmp=base-((1ll<<a[i])-1);
			now^=tmp;
			Print(now);
		}
	}
	return 0;
}