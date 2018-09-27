#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500009;

int a[MAXN],b[MAXN],c[MAXN];
int n,ans=0;

inline int read()
{
	int tmp=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}

bool calc(int v)
{
	for (int i=1;i<=v;i++)
		if (a[n-v+i]<b[i])
			return 0;
	return 1;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
		c[i]=read();
	for (int i=1;i<=n;i++)
		b[i]=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	int l=0,r=n+1,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (calc(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%d\n",l);
	return 0;
}