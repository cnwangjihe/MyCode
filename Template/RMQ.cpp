void RMQ()
{
	m=lg2[n];
	for (int i=1;i<=n;i++)
		Max[0][i]=h[i];
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (j+(1<<i)-1<=n)
				Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<(i-1))]);
	return ;
}

int query(int l,int r)
{
	int len=lg2[r-l+1];
	return max(Max[len][l],Max[len][r-(1<<len)+1]);
}

void prelg2()
{
	lg2[1]=0;
	for (int i=2;i<=n;i++)
		lg2[i]=lg2[i/2]+1;
	return ;
}