// Date      : 2018-12-31 01:04:14
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 200009;

int n,m;
int a[MAXN],b[MAXN],c[MAXN];

int main()
{
//	freopen("H.in","r",stdin);
//	freopen("H.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	if (n&1)
		printf("Alice\nBob\n");
	else
		printf("Bob\nAlice\n");
	return 0;
}