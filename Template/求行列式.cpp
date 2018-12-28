double DTMGauss(double (*a)[MAXN],int n)
{
	double ans=1;
	int id,cnt=0;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (fabs(a[j][i])-fabs(a[id][i])>eps)
				id=j;
		if (id!=i)
		{
			cnt++;
			for (int j=1;j<=n;j++)
				swap(a[id][j],a[i][j]);
		}
		if (fabs(a[i][i])<eps)
			return 0;
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			for (int k=n;k>=i;k--)
				a[j][k]-=a[i][k]*a[j][i]/a[i][i];
		}
	}
	for (int i=1;i<=n;i++)
		ans=ans*a[i][i];
	return ans*((cnt&1)?-1:1);
}