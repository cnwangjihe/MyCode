// Date      : 2019-01-04 22:49:57
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1097/problem/B
// Algorithm : None
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100;

int n,sum;
int v[MAXN];
int main()
{
//	freopen("CF1097B.in","r",stdin);
//	freopen("CF1097B.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&v[i]);
	}
	for (int i=0;i<(1<<n);i++)
	{
		sum=0;
		for (int j=0;j<n;j++)
			if (i>>j&1)
				sum-=v[j];
			else sum+=v[j];
		if(!(sum%360))
			return printf("YES\n"),0;
	}
	printf("NO\n");
	return 0;
}