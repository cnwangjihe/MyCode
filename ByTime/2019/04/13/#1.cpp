
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int d[1005][1005];//d[i][j] i为层数，j为鸡蛋数 
//目标是找到一个d(i-1,j)<n&&d(i,j)>=n;
int main()
{
	while(cin>>n>>m)  //n为层数 m为鸡蛋数
	{
		memset(d,0,sizeof(d));
		for(int i=1;i<=m;i++)
		{
			d[1][i]=1;
		}
		for(int i=1;i<=n;i++)
		{
			d[i][1]=i;
		}
		for(int i=2;i<=n;i++)
		{
			for(int j=2;j<=m;j++)
			{
				d[i][j]=d[i-1][j]+d[i-1][j-1]+1;  //这个和组合数的性质很相似，可以这这里在做些文章
			}
		}
		for(int i=2;i<=n;i++)   //这边其实还可以优化的最终可以优化到sqrt(n)
		{
			if(d[i][m]>=n&&d[i-1][m]<n)
			{
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
}