#include <bits/stdc++.h>

using namespace std;

const int MAXN = 24,
		  MAXS = (1<<MAXN);

int a[MAXN],b[MAXN],c[MAXN];
long long fb[MAXS],fc[MAXS];
int n,k,ans=0;

int main()
{
	freopen("2707.in","r",stdin);
	freopen("2707_40.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<n;i++)
		scanf("%d",&b[i]);
	for (int i=0;i<n;i++)
		scanf("%d",&c[i]);
	fb[0]=fc[0]=0;
	for (int i=1;i<(1<<n);i++)
	{
		for (int j=0;j<n;j++)
		{
			if (i&(1<<j))
			{
				fb[i]=fb[i^(1<<j)]+(a[j]-b[j]);
				fc[i]=fc[i^(1<<j)]+(a[j]-c[j]);
			//	cerr << "## " << i << " : " << fb[i] << ' ' << fc[i] << endl;
				break;
			}
		}
	}
	int cnt;
	for (int i=1;i<(1<<n);i++)
	{
		if (fb[i]<=0 || fc[i]<=0)
			continue;
		cnt=0;
		for (int j=0;j<n;j++)
			if (i&(1<<j))
				cnt++;
		if (cnt>=k)
		{
	//		cerr << i << endl;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}