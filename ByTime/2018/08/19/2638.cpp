#include <bits/stdc++.h>

using namespace std;

int n,m;

int main()
{
	freopen("2638.in","r",stdin);
	freopen("2638.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&m);
		printf("%d\n",min(n,m)*2-2);
	}
	return 0;
}