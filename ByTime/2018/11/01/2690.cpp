#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

char s[MAXN],t[MAXN];
bool used[MAXN];
int a[MAXN];
int n,m;

bool check(int p)
{
	bool flag=1;
	int q=0;
	for (int i=0;i<n;i++)
		used[i]=1;
	for (int i=1;i<=p;i++)
		used[a[i]-1]=0;
	for (int i=0;i<m;i++)
	{
		while ((s[q]!=t[i] || !used[q]) && q<n)
			q++;
		if (q==n)
			{flag=0;break;}
		q++;
	}
	return flag;
}
int main()
{
	freopen("2690.in","r",stdin);
	freopen("2690.out","w",stdout);
	scanf("%s%s",s,t);
	n=strlen(s),m=strlen(t);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int l=0,r=n+1;
	while (l+1<r)
	{
		int mid=(l+r)>>1;
		if (check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%d",l);
	return 0;
}