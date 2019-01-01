// Date      : 2018-12-28 23:09:24
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/D
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009;
long long INF = 998244353ll*MAXN+10;

char s[MAXN];
long long f[MAXN][10];
long long a[MAXN];
int n;

bool gett(char c,int k)
{
	if (c=='h')
		return (k==0);
	if (c=='a')
		return (k==1);
	if (c=='r')
		return (k==2);
	if (c=='d')
		return (k==3);
	return 0;
}

int main()
{
//	freopen("CF1096D.in","r",stdin);
//	freopen("CF1096D.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s+1);
	for (int i=1;i<=n;i++)
		scanf("%I64d",&a[i]);
	for (int i=0;i<=n+2;i++)
		for (int j=0;j<=3;j++)
			f[i][j]=INF;
	f[0][0]=0;
	for (int i=1;i<=n;i++) 
		for (int j=0;j<4;j++)
		{
			f[i][j+gett(s[i],j)]=min(f[i][j+gett(s[i],j)],f[i-1][j]);
			f[i][j]=min(f[i][j],f[i-1][j]+a[i]);
		}
	printf("%I64d\n",min(f[n][0],min(f[n][1],min(f[n][2],f[n][3]))));
	return 0;
}