#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1009;

int n,m,tot;
double ans1,ans2;
int a[MAXN][MAXN];
double p[MAXN][MAXN];

int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		for (int i=1;i<=n;i++)
		{
			tot=0;
			for (int j=1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
				tot+=a[i][j];
			}
			for (int j=1;j<=m;j++)
				p[i][j]=(double)1.0*a[i][j]/tot;
		}
		
		ans2=ans1=0.0;
		for (int i=1;i<=m;i++)
		{
			double las=p[1][i],tmp=p[1][i];
			for (int j=2;j<=n;j++)
			{
				tmp+=p[j][i];
				ans1+=las*p[j][i];
				las+=p[j][i]; 
			}
			ans2+=tmp*tmp;
		}
	//	ans1=ans1*2.0+n;
		printf("%0.2f\n",ans1*2+n);
	}
	return 0;
}
