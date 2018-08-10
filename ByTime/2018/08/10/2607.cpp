#include <bits/stdc++.h>

using namespace std;

bool flag;
int s,w,b,n;
int minx,maxx;
int ans[2],c[2];

int main()
{
	freopen("2607.in","r",stdin);
	freopen("2607.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		s=0;
		scanf("%d%d%d",&n,&minx,&maxx);
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&w,&b);
			s=(s*w+b)%2;
			if (!(w&1))
				flag=1;
		}
		if ((maxx-minx)&1)
			c[1]=c[0]=(maxx-minx+1)>>1;
		else
		{
			c[minx&1]=((maxx-minx)>>1)+1;
			c[(minx&1)^1]=(maxx-minx)>>1;
		}
		if (flag)
			ans[s]=c[0]+c[1],ans[s^1]=0;
		else
			ans[s]=c[0],ans[s^1]=c[1];
		printf("%d %d\n",ans[0],ans[1]);
	}
	return 0;
}