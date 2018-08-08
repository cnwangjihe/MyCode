#include <bits/stdc++.h>

using namespace std;

int n,m,k,d;

int main()
{
	freopen("2563.in","r",stdin);
	freopen("2563.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d%d",&n,&m,&k);
		d=n+m-k-1;
		printf("%d\n",max(0,min(m,min(n,min(d,n-d+m)))));
	}
	return 0;
}