// Date      : 2018-12-26 08:31:28
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 生成函数(OGF)
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 129;

long long a[MAXN],b[MAXN],f[MAXN];
int n;

int main()
{
//	freopen("HDU1028.in","r",stdin);
//	freopen("HDU1028.out","w",stdout);
	f[0]=1;
	for (int i=1;i<=120;i++)
		f[i]=0;
	for (int i=1;i<=120;i++)
	{
		for (int j=0;j<=120;j++)
			a[j]=0;
		for (int j=0;j<=120;j+=i)
			a[j]=1;
		for (int j=0;j<=120;j++)
		{
			b[j]=0;
			for (int k=0;k<=j;k++)
				b[j]+=a[k]*f[j-k];
		}
		for (int i=0;i<=120;i++)
			f[i]=b[i];
	}
	while (scanf("%d",&n)==1 && n)
		printf("%lld\n",f[n]);
	return 0;
}