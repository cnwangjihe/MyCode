#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;
const long long MOD = 1000000007;
int n,m;

long long ans[MAXN];

int main()
{
	int ttt;
	ans[1]=0,ans[2]=1,ans[3]=2;
	for (int i=4;i<=1000;i++)
		ans[i]=1ll*(ans[i-1]+ans[i-2])*(i-1)%MOD;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&m);
		printf("%lld\n",ans[n]);
	}
	return 0;
}