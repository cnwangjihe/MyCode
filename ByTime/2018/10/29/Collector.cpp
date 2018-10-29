#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10009;

int a[MAXN],b[MAXN];
int n,c1=0,c2=0;
char opt;
double ans=0,leftn=1000;

int main()
{
	freopen("Collector.in","r",stdin);
	freopen("Collector.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		do {opt=getchar();}
			while (opt!='T' && opt!='D');
		if (opt=='T')
			scanf("%d",&a[c1++]);
		else
			scanf("%d",&b[c2++]);
	}
	sort(a,a+c1);
	sort(b,b+c2);

	int i=0,j=0;
	for (int k=1;k<=n;k++)
	{
		if (leftn==0)
			break;
		if (j>=c2 || (i<c1 && a[i]<ans+(b[j]+leftn-1000)*k))
		{
			leftn-=(1.0*a[i]-ans)/(1.0*k);
			ans=a[i++];
		}
		else if (i>=c1 || (j<c2 && a[i]>ans+(b[j]+leftn-1000)*k))
		{
			ans+=(b[j]+leftn-1000)*k;
			leftn=1000-b[j++];
		}
		else
		{
			leftn=1000-b[j];
			ans=a[i];
			k++;
		}
	}
	ans+=leftn*(n+1);
	printf("%.0lf\n",ans);
	return 0;
}