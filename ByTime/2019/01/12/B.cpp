// Date      : 2019-01-11 22:42:14
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

char s[500009];
int p=0,r,n,tp,tr;
int ans=0;

int main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	scanf("%s",s);
	int i,j;
	n=strlen(s);
	for (i=0;i<n;i++) 
		if (s[i]!='[') ans++;else break;
	for (i++;i<n;i++) 
		if (s[i]!=':') ans++;else break;
	for (j=n-1;~j;j--) 
		if (s[j]!=']') ans++;else break;
	for (j--;~j;j--) 
		if (s[j]!=':') ans++;else break;
	
	if (i>=j) return printf("-1\n"),0;
	for (i++;i<j;i++) 
		if (s[i]!='|') ans++;
	printf("%d\n",n-ans);
	return 0;
}