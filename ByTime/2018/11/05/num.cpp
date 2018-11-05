#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tnode {long long v;int i;};

Tnode a[MAXN];
long long b[MAXN];
int ans[MAXN];
int n,Max=0;

void solve()
{
	int m=0,p;
	for (int i=1;i<=n;i++)
	{
		p=upper_bound(b+1,b+m+1,a[i].v)-b;
		if (p==m+1)
			m++;
		b[p]=a[i].v;
		ans[a[i].i]+=p;
	}
	return ;
}

inline long long read()
{
	char ch=0;
	int w=0;
	long long x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10ll+ch-'0',ch=getchar();
	return w?-x:x;
}

int main()
{
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);

	n=read();
	for (int i=1;i<=n;i++)
		a[i].v=read()-i,a[i].i=i;
	solve();
	for (int i=1;i<=n/2;i++)
		swap(a[i],a[n-i+1]);
	for (int i=1;i<=n;i++)
		a[i].v*=-1;
	solve();
	for (int i=1;i<=n;i++)
		Max=max(ans[i],Max);
	printf("%d\n",Max-1);
	return 0;
}