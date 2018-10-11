#include <bits/stdc++.h>

using namespace std;
int T,num,p;
long long mod,n,f[205],g[205],line[205],ff[205];
int	main()
{
	cin>>T;
	mod=1000000000000000000;
	ff[1]=1;ff[2]=2;
	for (int i=3;i<=200;i++)
	{
		ff[i]=ff[i-1]+ff[i-2];
		if (ff[i]>mod) {p=i;break;}
	}
	for (int o=1;o<=T;o++)
	{
		cin>>n;num=0;
		for (int i=1;i<=p;i++) line[i]=f[i]=g[i]=0;
		for (int i=p;i>=1;i--)
		{
			if (n>=ff[i])
			{num++;line[num]=i;n-=ff[i];}
		}
		for (int i=1;i<=num/2;i++) swap(line[i],line[num-i+1]);
		f[1]=1;g[1]=(line[1]-1)/2;
		for (int i=2;i<=num;i++)
		{
			f[i]=f[i-1]+g[i-1];
			g[i]=f[i-1]*((line[i]-1-line[i-1])/2)+g[i-1]*((line[i]-line[i-1])/2);
		}
		cout<<f[num]+g[num]<<endl;
	}
	return 0;
}
