#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int n;
int a[MAXN];

int main()
{
	int T;
	freopen("2656.in","r",stdin);
	freopen("2656.out","w",stdout);
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		printf("%d\n",(int)sqrt(abs(a[1]-a[n])));
	}
	return 0;
}
