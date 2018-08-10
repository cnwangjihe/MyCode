#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tdata
{
	int a,b,i;
	Tdata(){};
	bool operator==(const Tdata &t) {return this->a==t.a && this->b==t.b;}
	bool operator!=(const Tdata &t) {return !(*this==t);}
};

Tdata a[MAXN],q[MAXN];
long long sum[MAXN],cnt[MAXN],ans[MAXN],v[MAXN];
int n,qn,fp=1,m=1;
int start[MAXN],stop[MAXN];
int len[MAXN];
int line[MAXN];
//int tim=0;

bool _cmp(Tdata a,Tdata b) {return (a.a==b.a)?(a.b<b.b):(a.a<b.a);}

int main()
{
	freopen("2605.in","r",stdin);
	freopen("2605.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&len[i]);
		for (int j=0;j<len[i];j++)
		{
			scanf("%d",&a[m].a);
			v[i]+=a[m].a;
			a[m++].i=i;
		}
	}
	sort(a+1,a+m+1,_cmp);
	scanf("%d",&qn);
	for (int i=1;i<=qn;i++)
		scanf("%d%d",&q[i].a,&q[i].b),q[i].i=i;
	sort(q+1,q+1+qn,_cmp);
	for (int i=1;i<=qn;i++)
		if (q[i]!=q[i-1])
		{
			line[fp]=i;
			if (!start[q[i].a])
				start[q[i].a]=fp;
			stop[q[i].a]=fp++;
		}
	int u;
	for (int i=1;i<=m;i++)
	{
		sum[a[i].i]+=a[i].a;
		cnt[a[i].i]++;
		if (start[a[i].i])
			for (int j=start[a[i].i];j<=stop[a[i].i];j++)
			{
//				tim++;
				u=line[j];
				ans[q[u].i]+=cnt[q[u].b]*(long long)a[i].a-2*sum[q[u].b]+v[q[u].b]-(len[q[u].b]-cnt[q[u].b])*(long long)a[i].a;
			}
	}
	for (int i=1;i<=qn;i++)
		if (q[i]==q[i-1])
			ans[q[i].i]=ans[q[i-1].i];
	for (int i=1;i<=qn;i++)
		printf("%lld\n",ans[i]);
//	cerr << tim << '\n';
	return 0;
}
/*
 1 2 2 3 1 2 2 2 2 2 2 2
 2+3+3+1+2+3+3+3+3+3+3+3=32
 2:3
 3:1
 1:2

 6 6 
 12
 */