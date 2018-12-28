// Date      : 2018-12-27 14:28:42
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : DP
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

using std::cerr;

const int MAXN = 22,
		  MAXS = 1<<MAXN;

double f[MAXS];
double p[MAXN];
double np,sp;
int n;

int main()
{
//	freopen("HDU4336.in","r",stdin);
//	freopen("HDU4336.out","w",stdout);
	while (scanf("%d",&n)==1 && n)
	{
		np=1;
		for (int i=0;i<n;i++)
			scanf("%lf",&p[i]),np-=p[i];
		f[0]=0;
		for (int i=1;i<(1<<n);i++)
		{
			f[i]=1;sp=0;
			for (int j=0;j<n;j++)
			{
				if (!(i&(1<<j)))
					continue;
				sp+=p[j];
				f[i]+=f[i^(1<<j)]*p[j];
			}
		//	cerr << sp << ' ' << np << '\n';
			f[i]/=sp;
		}
		printf("%.6lf\n",f[(1<<n)-1]);
	}
	return 0;
}