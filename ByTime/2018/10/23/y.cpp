#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

char a[MAXN],b[MAXN];
int n,m,k;

int main()
{
	freopen("y.in","r",stdin);
	freopen("y.out","w",stdout);
	int t,l,r;
	scanf("%s\n%s",a,b);
	n=strlen(a);
	m=strlen(b);
	for (int i=0;i<n;i++)
		a[i]-='0';
	for (int i=0;i<m;i++)
		b[i]-='0';
	scanf("%d",&k);
	for (int i=0;i<k;i++)
	{
		scanf("%d%d%d",&t,&l,&r);
		if (t-1)
		{
			for (int j=l;j<=r;j++)
				a[i]^=1;
		}
		else
		{
			int ans=0;
			bool flag;
			for (int j=l;j+m-1<=r;j++)
			{
				flag=1;
				for (int p=0;p<m;p++)
					if (a[p+j]!=b[p])
					{
						flag=0;
						break;
					}
				ans+=flag;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}