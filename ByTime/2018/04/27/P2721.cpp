#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 10009;

int sum[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char date[20];
double f[400],v[MAXN];
int start[MAXN],t[MAXN];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=2;i<=12;i++)
		sum[i]+=sum[i-1];
	for (int i=0;i<n;i++)
	{
		scanf("%s%d%lf",date,&t[i],&v[i]);
		v[i]/=100.0;
		v[i]/=sum[12];
		start[i]=sum[(date[0]-'0')*10+date[1]-'0'-1]+(date[2]-'0')*10+date[3]-'0';
	//	cerr << v[i] << ' ' << start[i] << ' ' << t[i] << endl;
	}
	f[0]=100000.0;
	for (int i=1;i<=sum[12];i++)
	{
		f[i]=f[i-1];
		for (int j=0;j<n;j++)
			if (start[j]+t[j]-1==i)
				f[i]=max(f[i],f[start[j]-1]*(1.0+v[j]*(double)t[j]));
	}
	printf("%.2lf\n",f[sum[12]]);
	return 0;
}