 #include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mx=52;
int n;
int w[mx];
int cnt[mx];
//map<int,ll> mp[mx][1048580];
//map<int,ll>::iterator it;

long long search(int k,int s1,int s2)
{
	if (k==n+1)
		return s1==s2;
	long long ans=search(k+1,s1&w[k],s2)+search(k+1,s1,s2&w[k]);
	return ans;
}

void task()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	int full=(1<<20)-1,s=full;
	for (int i=1;i<=n;i++) s&=w[i];
	for (int i=1;i<=n;i++) w[i]-=s;
	sort(w+1,w+n+1);

	long long ans=search(1,full,full);
	printf("%lld\n",ans);
}

int main()
{
//	freopen("2733.in","r",stdin);
//	freopen("2733.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	while(t>0)
	{
		t--;
		task();
	}
	
	
	return 0;
}
