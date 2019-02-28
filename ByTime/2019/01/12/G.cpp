// Date      : 2019-01-11 23:30:14
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 500009;

struct LB{
	int b[100],n;

	LB(){n=0;}

	void insert(int x)
	{
		for (int j=30;~j;j--)
		{
			if (!(x&(1<<j)))
				continue;
			if (b[j])
				x^=b[j];
			else
			{
				b[j]=x;
				n++;
				for (int k=j-1;~k;k--)
					if (b[k] && (b[j]&(1<<k)))
						b[j]^=b[k];
				for (int k=j+1;k<30;k++)
					if (b[k] && (b[k]&(1<<j)))
						b[k]^=b[j];
				break;
			}
		}
	}
};

LB A;
int a[MAXN];
int n;

int main()
{
//	freopen("G.in","r",stdin);
//	freopen("G.out","w",stdout);

	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",a+i);
	for (int i=1;i<n;i++)
		a[i]^=a[i-1];
	if (a[n-1]==0)
		return printf("-1\n"),0;
	for (int i=0;i<n;i++)
		A.insert(a[i]);
	printf("%d\n",A.n);

	return 0;
}
