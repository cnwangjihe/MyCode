// Date      : 2019-01-04 22:58:58
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1097/problem/C
// Algorithm : None
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int frt[1000009],a[1000009];
int head,fp,sum;
int m,n;
char s[1000009];

int main()
{
//	freopen("CF1097C.in","r",stdin);
//	freopen("CF1097C.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%s",s);
		m=strlen(s);
		sum=0;
		frt[i]=100000;
		for (int j=0;j<m;j++)
		{
			sum+=(s[j]==')')?-1:1;
			frt[i]=min(sum,frt[i]);
		}
		if (sum>=0)
		{
			if (frt[i]>=0)
				a[fp++]=sum;
		}
		else
		{
			if (frt[i]==sum)
				a[fp++]=sum;
		}
	}
	int ans=0;
	std::sort(a,a+fp);
	while (head+1<fp)
	{
		if (a[head]==-a[fp-1])
			head++,fp--,ans++;
		else if (abs(a[head])>abs(a[fp-1]))
			head++;
		else fp--;
	}
	printf("%d\n",ans);
	return 0;
}