// Date    : 2018-12-19 21:57:34
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 100009;

struct Tnode{int sx,sy,ex,ey;};

Tnode a[MAXN];
int n;

bool check(int i,int j)
{
	if (a[i].sx>=a[j].ex)
		return 0;
	if (a[i].sy>=a[j].ey)
		return 0;
	if (a[i].ex<=a[j].sx)
		return 0;
	if (a[i].ey<=a[j].sy)
		return 0;
	return 1;
}

int main()
{
	freopen("2737.in","r",stdin);
	freopen("2737.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d%d",&a[i].sx,&a[i].sy,&a[i].ex,&a[i].ey),a[i].ex+=a[i].sx,a[i].ey+=a[i].sy;
	bool flag;
	for (int i=1;i<=n;i++)
	{
		flag=1;
		for (int j=i+1;j<=n && flag;j++)
		{
			if (check(i,j))
				flag=0;
		}
		printf("%s\n",flag?"DA":"NE");
	}
	return 0;
}