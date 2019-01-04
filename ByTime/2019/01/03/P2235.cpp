// Date      : 2019-01-03 07:49:33
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1000009;

int f[MAXN];
int n;

int main()
{
//	freopen("P2235.in","r",stdin);
//	freopen("P2235.out","w",stdout);
	scanf("%d",&n);
	f[1]=1;
	f[3]=3;
	f[2]=1;
	f[4]=1;
	for (int i=1;i*4<n;i++)
	{
		f[i*4+1]=2*f[i*2+1]-f[i];
		f[i*4+2]=f[i*2+1];
		f[i*4+3]=3*f[2*i+1]-2*f[i];
		f[i*4+4]=f[i*2+2];
	}
	for (int i=1;i<=n;i++)
		if (i==f[i])
			printf("%d : %d\n",i,f[i]);
	return 0;
}