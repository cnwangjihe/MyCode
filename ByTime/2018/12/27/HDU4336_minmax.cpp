// Date      : 2018-12-27 15:18:39
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const double eps = 1e-8;
const int MAXN = 22;

int n;
double p[MAXN];

double dfs(int k,double sum,int c)
{
	if (k==n)
	{
		if (!c)
			return 0;
		return 1.0/sum*(c&1?1:-1);
	}
	return dfs(k+1,sum+p[k],c+1)+dfs(k+1,sum,c);
}

int main()
{
//	freopen("HDU4336_minmax.in","r",stdin);
//	freopen("HDU4336_minmax.out","w",stdout);
	while (scanf("%d",&n)==1 && n)
	{
		for (int i=0;i<n;i++)
			scanf("%lf",&p[i]);
		printf("%.6lf\n",dfs(0,0,0));
	}
	return 0;
}