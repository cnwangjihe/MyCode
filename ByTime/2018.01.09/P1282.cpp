#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAXN = 1010;

int f[2][MAXN*20],a[MAXN],b[MAXN];
int n,sum=0;

int Min(int a,int b) {return (~a)?((a<b)?a:b):b;}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		sum+=abs(a[i]-b[i]);
	}
	memset(f,-1,sizeof f);
	f[1][2*sum+b[1]-a[1]]=1;
	f[1][2*sum-b[1]+a[1]]=f[1][2*sum+b[1]-a[1]]-2+(3%2);
	for (int i=1;i<n;i++)
	{
		int cur=(i&1),nxt=(cur^1);
		memset(f[nxt],-1,sizeof f[nxt]);
		for (int j=sum;j<=3*sum;j++)
			if (~f[cur][j])
			{
				f[nxt][j+b[i+1]-a[i+1]]=Min(f[nxt][j+b[i+1]-a[i+1]],f[cur][j]+1);
				f[nxt][j+a[i+1]-b[i+1]]=Min(f[nxt][j+a[i+1]-b[i+1]],f[cur][j]);
			}
	}
	for (int i=2*sum;i<=3*sum;i++)
		if ((~f[n&1][i]) || (~f[n&1][sum*4-i]))
			return printf("%d\n",min(f[n&1][i],f[n&1][4*sum-i]))&0;
	return 0;
}
