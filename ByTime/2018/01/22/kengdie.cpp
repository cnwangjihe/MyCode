#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009;

int len=0,n=0,m=0,ans;
int a[MAXN*3],x[MAXN],q[MAXN];
bool ap[MAXN];
int val[20][MAXN];

int main()
{
	freopen("kengdie.in","r",stdin);
	freopen("kengdie.out","w",stdout);
	memset(ap,0,sizeof ap);
	while (scanf("%d",&a[++len])==1);
	len--;
	for (int i=1;i<=len;i++)
	{
		if (ap[a[i]])
		{
			if ((len-i+1)%2) n--;
			m=len-n;
			m/=2;
			break;
		}
		ap[a[i]]=1;
		n++;
	}
//	cerr << n << ' ' << m << endl;
	if (!m) return 0;
	for (int i=n+1;i<=len;i++)
		if ((len-i)&1)
			x[(i-n+1)/2]=a[i];
		else
			q[(i-n)/2]=a[i];
	for (int i=1;i<=n;i++)
		val[0][i]=a[i];
	for (int i=1;(1<<i)<=MAXN;i++)
		for (int j=1;j<=n;j++)
			val[i][j]=val[i-1][val[i-1][j]];
	for (int i=1;i<=m;i++)
	{
		ans=x[i];
	//	cerr << ans << ' ';
		for (int j=0;(1<<j)<=q[i];j++)
			if (q[i]&(1<<j))
				ans=val[j][ans];
		printf("%d\n",ans);
	}
	return 0;
}
