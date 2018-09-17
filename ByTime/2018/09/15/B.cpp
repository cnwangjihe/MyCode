#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

int n,m,p;
int sum;
int f[MAXN][MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	memset(f,0,sizeof f);
	f[1][1]=m;
	for (int i=1;i<n;i++)
	{
		sum=0;
		for (int j=m-1;j>=1;j--)
		{
			(f[i+1][j+1]+=1ll*(m-j)*f[i][j]%p)%=p;
			f[i+1][j]=(f[i][j]+sum)%p;
			(sum+=f[i][j])%=p;
		}
	}
	int ans=0;
	for (int i=1;i<m;i++)
		ans=(ans+f[n][i])%p;
	printf("%d\n",ans);
	return 0;
}