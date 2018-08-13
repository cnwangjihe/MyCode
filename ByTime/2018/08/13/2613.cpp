#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

double suma,sumb,ans;
double a[MAXN],b[MAXN];
int n;

int main()
{
	freopen("2613.in","r",stdin);
	freopen("2613.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i],&b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for (int i=n,j=n;i;)
	{
		suma+=a[i--];
		while (j && min(suma-(n-i)-(n-j),sumb-(n-i)-(n-j))<min(suma-(n-i)-(n-j+1),(sumb+b[j])-(n-i)-(n-j+1)))
			sumb+=b[j--];
	//	cerr << suma << ' ' << sumb << ' ' << i << ' ' << j <<endl;
		ans=max(ans,min(suma-(n-i)-(n-j),sumb-(n-i)-(n-j)));
	}
	printf("%.4lf\n",ans);
	return 0;
}