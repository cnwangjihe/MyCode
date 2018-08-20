#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000009;

long long ans,sum;
long long a[MAXN],b[MAXN],v[MAXN];
long long c[MAXN];
int pos,n,m=0;
long long p;

inline void update(int x)
{
	for (;x<=m;x+=x&-x)
		c[x]++;
	return ;
}

inline int query(int x)
{
	int ans=0;
	for (;x>0;x-=x&-x)
		ans+=c[x];
	return ans;
}

int main()
{
	freopen("2640.in","r",stdin);
	freopen("2640.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	scanf("%lld",&p);
	for (int i=1;i<=n;i++)
		v[i]=a[i]-p;
	for (int i=1;i<=n;i++)
		a[i]=a[i]-p+a[i-1];
	a[n+1]=0;
	sort(a+1,a+n+2);
	for (int i=1;i<=n+1;i++)
	{
		b[++m]=a[i];
		while (i+1<=n+1 && a[i]==a[i+1])
			i++;
	//	cerr << b[m] << endl;
	}
	for (int i=0;i<=n;i++)
	{
		sum+=v[i];
	//	cerr << sum << endl;
		pos=lower_bound(b+1,b+1+m,sum)-b;
		ans+=query(pos);
		update(pos);
	}
	printf("%lld\n",ans);
	return 0;
}