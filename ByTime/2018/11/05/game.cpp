#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20009;

int a[MAXN];
int n,ans=0;

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);

	scanf("%d",&n);
	for (int i=0;i<n;i++) 
		scanf("%d",&a[i]);
	sort(a,a+n);
	for (int i=0;i<n;i++)
	{
	//	cerr << "## " << a[i] << ' ' << a[i]-ans << '\n';
		ans=max(ans,a[i]-ans);
	}
	printf("%d\n",ans);
	return 0;
}
