n m
a[i][j]

f[i]

g[i]

dp[i][j] = INF   i=1~n   j=1~1023
dp[?][0] = ss[i]
dp[i][1<<g[i]]=ss[i] 

for(j=0; j<1024; j++)
{
  for (i=1; i<=n; i++)
	for (k=(j-1&j); k; k=(k-1&j))
	  dp[i][j]=min(dp[i][j],dp[i][k]+dp[i][j^k]-ss[i]);
  for (i=1; i<=n; i++) d[i]=dp[i][j];
  for (i=1; i<=n; i++) s[i]=i,v[i]=true;
  l=1; r=n;
  while (l<=r)
  {
	now=s[l]; l++;
	for (i=1; i<=n; i++) 
	  if (a[now][i] && d[i]>d[now]+1)
	  {
	d[i]=d[now]+ss[now];
	if (!v[i]) {r++; s[r]=i; v[i]=true;}
	  }
	v[now]=false;
  }
  for (i=1; i<=n; i++) dp[i][j]=d[i];
}