// Date      : 2018-12-30 22:44:13
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1009;
int n;
std::pair<int,int> a[MAXN],b[MAXN];

int main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	for (int i=0;i<n;i++)
		scanf("%d%d",&b[i].first,&b[i].second);
	std::sort(a,a+n);
	std::sort(b,b+n);
	printf("%d %d\n",a[0].first+b[n-1].first,a[0].second+b[n-1].second);
	return 0;
}