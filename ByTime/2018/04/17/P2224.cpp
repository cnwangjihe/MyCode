#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 6009,
		  INF  = 1000000009;

int n,a,b,c,Max=0,ans=INF;
int f[6*MAXN];

int main()
{
	scanf("%d",&n);
	fill(f,f+6*MAXN,INF);
//	cerr << f[0] << ' ' << INF << endl;
	f[0]=0;
	for (int i=0;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c); 
		a = a==0?INF:a;
		c = c==0?INF:c;
		b = b==0?INF:b;
		Max+=min(a,min(b,c)); 
		for(int j=Max;j>=0;j--)
		{
			if (b==INF) 
				f[j]=b;
			else
				f[j]+=b;
			if (j>=a)
				f[j]=min(f[j-a],f[j]);
			if (j>=c)
				f[j]=min(f[j-c]+c,f[j]);
		}
	}
	for (int i=Max;i>=0;i--)
//		cerr << i <<' ' << f[i] << '\n',
		ans=min(ans,max(i,f[i]));
	printf("%d\n",ans);
	return 0;
}