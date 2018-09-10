#include<bits/stdc++.h>
using namespace std;

const int MAXN = 550,
		  MOD  = 1000000007;

int n,a,b,ans;
int s[MAXN],S[MAXN],vis[MAXN];

int main()
{
	int T;
	freopen("2650.in","r",stdin);
	freopen("2650.out","w",stdout);
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		scanf("%d%d%d",&n,&a,&b);
		for (int i=0;i<n;i++)
			scanf("%d",&s[i]);
		for (int i=0;i<=b;i++)
			S[i]=s[i%n]+n*(i/n);
		int cnt;
		for (int i=a;i<=b;i++)
			for (int j=i;j<=b;j++)
			{
				for (int k=i;k<=j;k++)
				{
					if (vis[k])
					{
						vis[k]=0;
						continue;
					}
					cnt=1;
					for (int l=k+1;l<=j;l++)
						if (S[l]==S[k])
							vis[l]=1,cnt++;
					ans=(ans+cnt*cnt*S[k])%MOD;					
				}
			}
		printf("%d\n",ans);
	}
	return 0;
}