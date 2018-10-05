#include <bits/stdc++.h>

using namespace std;
const long long mod=1000000007;
int n,T,shi[105],dp[15][1050][2];
long long f1[1050],f2[1050],ans;
int main()
{
	cin>>T;
	for (int o=1;o<=T;o++)
	{
		cin>>n;
		shi[0]=0;
		while (n>0)
		{
			shi[0]++;
			shi[shi[0]]=n%10;
			n/=10;
		}
		for (int i=1;i<=shi[0]/2;i++)
		swap(shi[i],shi[shi[0]-i+1]);
	for (int i=1;i<=shi[0];i++)
		cerr << shi[i] << ' ';
		for (int i=0;i<=shi[0]+1;i++)
		{
			for (int j=0;j<=1024;j++)
				dp[i][j][1]=dp[i][j][0]=0;
		}
		dp[0][0][1]=1;
		for (int i=0;i<shi[0];i++)
		{
			
			for (int j=0;j<(1 << 10);j++)
			{
				for (int k=0;k<=9;k++)
				{
					if (j==0 && k==0)
					dp[i+1][j][0]+=dp[i][j][0];
					else
					dp[i+1][j | (1 << k)][0]+=dp[i][j][0];
				}
				for (int k=0;k<=shi[i+1];k++)
				{
					if (j==0 && k==0)
					dp[i+1][j][0]+=dp[i][j][1];
					else
					{
					if (k<shi[i+1])
					dp[i+1][j | (1 << k)][0]+=dp[i][j][1];
					else 
					dp[i+1][j | (1 << k)][1]+=dp[i][j][1];
					}
				}
			}
		}
	dp[shi[0]][0][0]=0;
		for (int i=0;i<=shi[0];i++)
		{
			for (int j=0;j<(1 << 10);j++)
				cerr << dp[i][j][1] << ' ';
			cerr << endl;
		}
	for (int i=0;i<=1024;i++) f2[i]=f1[i]=0;
	f1[0]=1;
	for (int i=1;i<(1 << 10);i++)
	{
		for (int j=0;j<(1 << 10);j++)f2[j]=f1[j];
		for (int j=0;j<(1 << 10);j++)
		if ((j & i)==0)
		{
			f2[j+i]=(1ll*f2[j+i]+1ll*f1[j]*(dp[shi[0]][i][0]+dp[shi[0]][i][1]))%mod;
		}
		swap(f1,f2);
	}
	ans=0;
	for (int i=1;i<(1 << 10);i++) ans=(ans+f1[i])%mod;
	printf("Case %d:",o);
	cout<<ans<<endl;
	}
	return 0;
}