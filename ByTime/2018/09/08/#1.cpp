#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[MAXN];
long long sum1,sum2,ans;
int n,w;

bool _cmp(int a,int b) {return a>b;}

int main()
{
	freopen("A.in","r",stdin);
	freopen("#1.out","w",stdout);
	scanf("%d%d",&n,&w);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	sort(a+1,a+n+1,_cmp);
	sort(b+1,b+n+1,_cmp);
	for (int i=0;i<=n;i++)
	{
		sum1+=a[i];
		sum2=0;
		for (int j=0;j<=n;j++)
		{
			sum2+=b[j];
			ans=max(ans,min(sum2,sum1)-1ll*w*(1ll*i+j));
		}
	}
	printf("%lld\n",ans);
	return 0;
}