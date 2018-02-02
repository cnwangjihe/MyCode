#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1008;

int ans=0,n,q,x,y;
int a[MAXN],b[MAXN],c[MAXN],f[MAXN];

int main()
{
	freopen("gift.in","r",stdin);
	freopen("gift4.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		ans=0;
		scanf("%d%d",&x,&y);
		memset(f,-1,sizeof f);
		f[0]=0;
		for (int j=0;j<n;j++)
			if (j!=x)
				for (int k=0;k<c[j];k++)
					for (int v=MAXN-a[j];v>=0;v--)
						if (~f[v])
							f[v+a[j]]=max(f[v+a[j]],f[v]+b[j]);
		for (int j=0;j<=y;j++) ans=max(ans,f[j]);
		printf("%d\n",ans);
	}
} 
