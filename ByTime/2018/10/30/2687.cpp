#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[MAXN],r[MAXN];
long long ans;
int n,top;

int gcd(int a,int b) {return (a%b)?gcd(b,a%b):b;}

int main()
{
	freopen("2687.in","r",stdin);
	freopen("2687.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		top=0;ans=0;
		int t;
		for (int i=n;i;i--)
		{
			for (int j=1;j<=top;j++)
				b[j]=gcd(b[j],a[i]);
			b[++top]=a[i];
			r[top]=i;
			t=1;
			for (int j=2;j<=top;j++)
			{
				if (b[j]==b[t])
					continue;
				b[++t]=b[j];
				r[t]=r[j];
			}
			top=t;
			for (int j=1;j<=top;j++)
				ans=max(ans,1ll*b[j]*(r[j]-i+1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}