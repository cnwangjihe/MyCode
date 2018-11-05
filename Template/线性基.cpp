#include <bits/stdc++.h>

using namespace std;

const int MAXN = 52;

long long a[MAXN],b[MAXN];
long long ans=1;
int n,m;
char c;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			do {c=getchar();}
				while (c!='O' && c!='X');
			if (c=='O')
				a[i]|=(1ll<<j);
		}
		for (int j=n-1;~j;j--)
		{
			if (!(a[i]&(1ll<<j)))
				continue;
			if (b[j])
				a[i]^=b[j];
			else
			{
				b[j]=a[i];
				for (int k=j-1;~k;k--)
					if (b[k] && (b[j]&(1ll<<k)))
						b[j]^=b[k];
				for (int k=j+1;k<n;k++)
					if (b[k] && (b[k]&(1ll<<j)))
						b[k]^=b[j];
				break;
			}
		}
	}
	for (int i=0;i<n;i++)
		if (b[i])
			ans*=2ll;
	printf("%lld\n",ans%2008ll);
	return 0;
}