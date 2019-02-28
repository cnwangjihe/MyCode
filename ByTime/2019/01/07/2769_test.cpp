// Date      : 2019-01-07 20:03:11
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 105;

int a[MAXN];
bool used[MAXN];
int n;

void dfs(int k)
{
	if (k==n)
	{
		for (int i=0;i<n;i++)
			printf("%d ",a[i]);
		putchar('\n');
		return ;
	}
	for (int i=0;i<n-1;i++)
	{
		if (used[i])
			continue;
		swap(a[i],a[i+1]);
		used[i]=1;
		dfs(k+1);
		used[i]=0;
		swap(a[i],a[i+1]);
	}
	return ;
}

int main()
{
//	freopen("2769_test.in","r",stdin);
//	freopen("2769_test.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		a[i]=i;
	dfs(1);
	return 0;
}