#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[MAXN];
long long v,sum1,sum2,ans;
int n,w;

bool _cmp(int a,int b) {return a>b;}

int main()
{
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	scanf("%d%d",&n,&w);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	sort(a+1,a+n+1,_cmp);
	sort(b+1,b+n+1,_cmp);
	int j=1;
	for (int i=0;i<=n;i++)
	{
		sum1+=a[i];
		while (j<=n && sum2+b[j]<=sum1)
		{
			sum2+=b[j++];
			v=sum2-(1ll*i+j-1)*1ll*w;
			ans=max(v,ans);
		}
		if (j<=n)
		{
			v=sum1-(i+j)*w;
			ans=max(v,ans);
		}
	}
	printf("%lld\n",ans);
	return 0;
}