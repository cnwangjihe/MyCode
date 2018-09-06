#include<bits/stdc++.h>
using namespace std;
#define mod 1000000009
#define N 10
#define L 55
#define S 305
#define P 22

int n,p,f[L][N][S][P],pre[L][N][S][P],lim[N][L],vs[N];
long long st[N],nd[N],q[N];

int Solve()
{
int i,j,k,t,ans,maxi,small,big;
long long bn;
	for (i=0;i<n;i++)
	if  (q[i]<0) return 0;
	maxi=1;
	memset(lim,0,sizeof(lim));
	for (i=0;i<n;i++)
	{
		vs[i]=0;
		for (bn=q[i];bn;bn/=p) lim[i][vs[i]++]=bn%p;
		if  (vs[i]<=0) lim[i][vs[i]++]=0;
		maxi=max(maxi,vs[i]);
	}
	for (i=0;i<=maxi+3;i++)
		for (j=0;j<=n;j++)
			for (k=0;k<1<<n;k++)
				for (t=0;t<=p;t++) f[i][j][k][t]=pre[i][j][k][t]=0;
	f[0][0][0][0]=1;
	for (i=0;i<=maxi;i++)
	{
		for (j=0;j<=n;j++)
		{
			for (k=0;k<1<<n;k++)
			{
				for (t=1;t<p;t++) (pre[i][j][k][t]+=pre[i][j][k][t-1])%=mod;
				for (t=0;t<p;t++) (f[i][j][k][t]+=pre[i][j][k][t])%=mod;
				if  (j<n)
				{
					for (t=0;t<p;t++)
					if  (f[i][j][k][t])
					{
						// kaolv   p^i    di j wei
						if  (lim[j][i]+t<p) (f[i][j+1][k][t+lim[j][i]]+=f[i][j][k][t])%=mod;//==
						small=min(lim[j][i]-1,p-1-t);
						if  (small>=0)//<
						{
							(pre[i][j+1][k&(((1<<n)-1)^(1<<j))][t]+=f[i][j][k][t])%=mod;
							(pre[i][j+1][k&(((1<<n)-1)^(1<<j))][t+small+1]-=f[i][j][k][t])%=mod;
						}
						big=lim[j][i]+1;
						if  (big<=p-1-t)
						{
							(pre[i][j+1][k|(1<<j)][t+big]+=f[i][j][k][t])%=mod;
							(pre[i][j+1][k|(1<<j)][p]-=f[i][j][k][t])%=mod;
						}
					}
				}
			}
		}
		for (k=0;k<1<<n;k++)
			for (t=0;t<p;t++) (f[i+1][0][k][0]+=f[i][n][k][t])%=mod;
	}
	/*
	for (i=0;i<=maxi+1;i++)
		for (j=0;j<=n;j++)
			for (k=0;k<1<<n;k++)
				for (t=0;t<=p;t++)
				if  (f[i][j][k][t]) printf("f[%d][%d][%d][%d] = %d\n",i,j,k,t,f[i][j][k][t]);
				*/
	ans=0;
	for (i=0;i<p;i++) (ans+=f[maxi+1][0][0][i])%=mod;
	return ans;
}

int main()
{
int cas,dt,i,j,flag,temp,ans;
//    freopen("2647.in","r",stdin);
//    freopen("2647.out","w",stdout);
	scanf("%d",&cas);
	for (dt=1;dt<=cas;dt++)
	{
		scanf("%d%d",&n,&p);
		for (i=0;i<n;i++) scanf("%lld",&st[i]);
		for (i=0;i<n;i++) scanf("%lld",&nd[i]);
		ans=0;
		for (i=0;i<1<<n;i++)
		{
			flag=1;
			for (j=0;j<n;j++)
			if  ((1<<j)&i)
			{
				q[j]=st[j]-1;
				flag=-flag;
			}	else q[j]=nd[j];
			temp=Solve();
		//	printf("\nans[%d] = %d\n\n",i,flag*temp);
			(ans+=temp*flag)%=mod;
		}
		(ans+=mod)%=mod;
		printf("Case %d: %d\n",dt,ans);
	}
}