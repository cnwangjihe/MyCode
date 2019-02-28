// Date      : 2019-02-25 10:12:12
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 10009;

int f[MAXN][MAXN];
int s[MAXN];
int n;

int main()
{
	freopen("sanrd.in","r",stdin);
	freopen("sanrd.out","w",stdout);
	memset(f,0x3f,sizeof f);
	do {s[0]=getchar()-'0';}
		while (s[0]<1 || s[0]>9);
	do {s[++n]=getchar()-'0';}
		while (s[n]>=1 && s[n]<=9);
	for (int i=0;i<=n;i++)
		f[i][i]=0;
	for (int k=1;k<=n;k++)
		for (int i=0;i<=n && i+k<=n;i++)
			for (int p=i;p<i+k;p++)
				f[i][i+k]=min(f[i][i+k],max(f[i][p],f[p+1][i+k])+s[p]);
	printf("%d\n",f[0][n]);
	return 0;
}