#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3009;

int fp=2,n;
int a[MAXN];
int c[MAXN*MAXN][2];
int cnt[MAXN*MAXN];

void print(int u)
{
	if (!u)
		return ;
	if (cnt[u]>1)
		printf("%d\n",cnt[u]);
	print(c[u][0]);
	print(c[u][1]);
	return ;
}

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		do {a[i]=getchar()-'0';}
			while (a[i]!=0 && a[i]!=1);
	}
	int u;
	for (int i=0;i<n;i++)
	{
		u=1;
		for (int j=i;j<n;u=c[u][a[j++]],cnt[u]++)
			if (!c[u][a[j]])
				c[u][a[j]]=fp++;
	}
	print(1);
	return 0;
}
