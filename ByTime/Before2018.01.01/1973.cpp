#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n,m,p,mi,h[200],l[200],map[200][200],s;
bool boo;
int main()
{
	freopen("1973.in","r",stdin);
	freopen("1973.out","w",stdout);
	cin>>n>>m;
	p=1000;mi=1000000007;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)scanf("%d",&map[i][j]);
	}
	for (int i=0;i<=map[1][1];i++)
	{
		h[1]=i;l[1]=map[1][1]-i;s=h[1]+l[1];
		for (int j=2;j<=m;j++)
		{l[j]=map[1][j]-h[1];s+=l[j];}
		for (int j=2;j<=n;j++)
		{h[j]=map[j][1]-l[1];s+=h[j];}
		boo=true;
		for (int j=1;j<=n;j++)
		for (int k=1;k<=m;k++)if (map[j][k]!=h[j]+l[k] || h[j]<0 || l[k]<0){boo=false;break;}
		if (boo==true && s<mi){mi=s;p=i;} 
	}
	if (mi==1000000007)printf("-1");
	else 
	{
		h[1]=p;l[1]=map[1][1]-p;
			for (int j=2;j<=m;j++) l[j]=map[1][j]-h[1];
		    for (int j=2;j<=n;j++) h[j]=map[j][1]-l[1];
		    printf("%d\n",mi);
		    for (int j=1;j<=m;j++)
		    for (int k=1;k<=l[j];k++)printf("col %d\n",j);
		     for (int j=1;j<=n;j++)
		    for (int k=1;k<=h[j];k++)printf("row %d\n",j);
	}
	return 0;
}
