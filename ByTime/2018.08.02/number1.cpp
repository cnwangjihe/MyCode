#include <bits/stdc++.h>

using namespace std;

int n,m,k,d;
int ans;

int main()
{
	freopen("number.in","r",stdin);
	freopen("number1.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (abs(i-n)+abs(j-m)==k)
					ans++;
		printf("%d\n",ans);
	}
	return 0;
}