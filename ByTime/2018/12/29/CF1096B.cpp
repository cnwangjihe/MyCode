// Date      : 2018-12-28 22:39:46
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/B
// Algorithm : 
// Notice    : None

#include<bits/stdc++.h>

const int MOD = 998244353;

char a[200009];
long long n,l=1,r;

int main()
{
//	freopen("CF1096B.in","r",stdin);
//	freopen("CF1096B.out","W",stdout);
	scanf("%lld",&n);
	scanf("%s",a);

	for (l=1;l<n && a[0]==a[l];)
		l++;

	for (r=n-2;r!=-1 && a[r]==a[n-1];)
		r--;
	r=n-r-1;
	if (l==n)
		return printf("%lld\n",n*(n+1)/2%MOD),0;
	if (a[0]==a[n-1])
		printf("%lld\n",(l+1)*(r+1)%MOD);
	else printf("%lld\n",l+r+1);

	return 0;
}