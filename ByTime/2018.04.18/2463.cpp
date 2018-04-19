#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e+6 + 10;
const int INF = 0x7fffffff;

struct pi{
	int a,b;
}a[maxn];

int n;
map<int,int> cnt;

int check(int x)
{
	int i,cnta=0,cntb=0;
	
	for(i=0;i<n;i++) 
	{
		if(a[i].a==x) cnta++;
		else if(a[i].b==x) cntb++;
	}
	if(cnta>=(n+1)/2) return 0;
	if(cnta+cntb<(n+1)/2) return INF;
	return (n+1)/2-cnta;
}

int main()
{
	freopen("2463.in","r",stdin);
	freopen("2463.out","w",stdout);
	
	int i;
	int ans=INF;
	
	scanf("%d",&n);
	for(i=0;i<n;i++) 
	{
		scanf("%d%d",&a[i].a,&a[i].b);
		cnt[a[i].a]++;cnt[a[i].b]++;
	}
	
	for(map<int,int>::iterator mit=cnt.begin();mit!=cnt.end();mit++) 
	{
		if(mit->second>=(n+1)/2) ans=min(ans,check(mit->first));
	}
	
	if(ans==INF) printf("Impossible\n");
	else printf("%d\n",ans);

	return 0;
}
