#include <bits/stdc++.h>

using namespace std;

const int MAXS = 258;
const int MOD = 30031;

int s=0,n,k,p;
int stat[MAXS];

struct Matrix
{
	int a[MAXS][MAXS];
	Matrix () {memset(a,0,sizeof a);}
	void set()
	{
		for(int i=1;i<=s;i++)
			a[i][i]=1;
		return ;
	}
	Matrix operator*(const Matrix &t)
	{
		Matrix ans;
		for(int i=1;i<=s;i++)
			for(int j=1;j<=s;j++)
				for(int k=1;k<=s;k++)
					ans.a[i][j]+=((this->a[i][k])*t.a[k][j])%MOD,
					ans.a[i][j]%=MOD;
		return ans;
	}
};

Matrix qpower(Matrix a,int n)
{
	Matrix ans;
	ans.set();
	for (int i=0;(1<<i)<=n;i++,a=a*a)
		if ((1<<i)&n)
			ans=ans*a;
	return ans;
}

Matrix build()
{
	Matrix tar;
	for (int i=1;i<=s;i++)
		for (int j=1;j<=s;j++)
		{
			int tmp=((stat[i]<<1)^(1<<p)^stat[j]);
			if (tmp==(tmp&(-tmp)))
				tar.a[i][j]=1;
		}
	return tar;
}

void dfs(int p,int step,int st)
{
	if (step==k) {stat[++s]=st;return ;}
	for (int i=p-1;i;i--)
		dfs(i,step+1,st+(1<<(i-1)));
	return ;
}

int main()
{
	freopen("2617.in","r",stdin);
	freopen("2617.out","w",stdout);
	scanf("%d%d%d",&n,&k,&p);
	dfs(p,1,1<<(p-1));
//	cerr << s << endl;
	Matrix a,b,ans;
	a=build();
	b=qpower(a,n-k);
	ans.a[1][1]=1;
	ans=ans*b;
//	cerr << b.a[1][1] << endl;
	printf("%d\n",ans.a[1][1]);
	return 0;
}