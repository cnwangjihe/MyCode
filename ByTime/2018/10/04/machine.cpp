#include <bits/stdc++.h>

using namespace std;

const int MAXN = 39,
		  MOD  = 2017;

struct Matrix
{
	int v[MAXN][MAXN];
	int n;
	Matrix(){memset(v,0,sizeof v);}
	void Reset()
	{
		for (int i=0;i<n;i++)
			v[i][i]=1;
		return ;
	}
	Matrix operator *(const Matrix &a)
	{
		Matrix ans;
		ans.n=n;
		for (int i=0;i<n;i++)
			for (int k=0;k<n;k++)
			{
				if (v[i][k]==0ll)
					continue;
				for (int j=0;j<n;j++)
					(ans.v[i][j]+=v[i][k]*a.v[k][j]%MOD)%=MOD;
			}
		return ans;
	}
};

Matrix a,b;
int n,m,k,ans=0;

Matrix qpow(Matrix a,int k)
{
	Matrix ans;
	ans.n=n+1;
	ans.Reset();
	for (int i=0;(1<<i)<=k;i++,a=a*a)
		if (k&(1<<i))
			ans=ans*a;
	return ans;
}

int main()
{
	freopen("machine.in","r",stdin);
	freopen("machine.out","w",stdout);
	scanf("%d%d",&n,&m);
	int x,y;
	a.n=n+1;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		a.v[x][y]=a.v[y][x]=1;
	}
	scanf("%d",&k);
	for (int i=0;i<=n;i++)
		a.v[i][i]=a.v[i][0]=1;
	b=qpow(a,k);
    for (int i=0;i<=n;i++)
    	(ans+=b.v[1][i])%=MOD;
    printf("%d\n",ans);
    return 0;
}