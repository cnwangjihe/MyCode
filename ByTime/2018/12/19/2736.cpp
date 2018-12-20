// Date    : 2018-12-19 20:54:24
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

const int MAXN = 1009;

double f[MAXN][MAXN];
double P1,P2,P3,P4,t;
int l1,l2,p1,p2;
double ans;

int main()
{
	freopen("2736.in","r",stdin);
	freopen("2736.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		memset(f,0,sizeof f);
		scanf("%d%d%d%d",&l1,&l2,&p1,&p2);
		P1=1.0/p1,P2=1.0/p2;
		P3=1-P1,P4=1-P2;
		f[0][0]=1;
		t=1-P3*P4;
		for (int i=0;i<=l1;i++)
			for (int j=0;j<=l2;j++)
			{
				if (!i && !j)
					continue;
				if (i && j!=l2)
					f[i][j]+=P1*P4*f[i-1][j];
				if (j && i!=l1)
					f[i][j]+=P3*P2*f[i][j-1];
				if (i && j)
					f[i][j]+=P1*P2*f[i-1][j-1];
				f[i][j]=f[i][j]/t;
			}
		for (int i=0;i<l2;i++) 
			ans+=f[l1][i];
		printf("%.16lf\n",ans);
	}
	return 0;
}