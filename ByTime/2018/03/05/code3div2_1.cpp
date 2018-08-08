#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 101009;

struct Tnum{int v,i;};

Tnum a[MAXN],f[MAXN];
int T,n,cnt,ans;
int b[MAXN];

bool _cmp(Tnum a,Tnum b) {return a.v<b.v;}

int main()
{
	scanf("%d",&T);
	for (;T;T--)
	{
		memset(f,0,sizeof f);
		cnt=ans=0;
		scanf("%d",&n);
		for (int i=0;i<n;i++)
			scanf("%d",&a[i].v);
		sort(a,a+n,_cmp);
		a[n].v=-1;
		for (int i=0;i<n;i++)
		{
			while (a[i].v==a[i+1].v) a[i].i=cnt,i++;
			if (i<n) a[i].i=cnt++;
		}
		for (int i=0;i<n;i++)
			f[a[i].i].v++,f[a[i].i].i=a[i].v;
		sort(f,f+cnt,_cmp);
		for (int i=cnt-1;~i;i--)
		{
			b[ans++]=f[i].i;
			if (i==0 || f[i].v!=f[i-1].v)
				break;
		}
		if (cnt==ans)
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n",ans);
		sort(b,b+ans);
		for (int i=0;i<ans;i++)
			printf("%d ",b[i]);
		putchar('\n');
	}
	return 0;
}
