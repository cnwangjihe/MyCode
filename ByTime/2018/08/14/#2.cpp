#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

const int mod=30031,N=205;
int n,K,p,cnt;
int fc[30],sta[N];

struct Matrix
{
	int a[N][N];
	Matrix(){memset(a,0,sizeof(a));}
	void Reset(){for(int i=1;i<=cnt;++i) a[i][i]=1;}
}A,B,ans;

int up(int &x,int y) {x+=y;if(x>=mod) x-=mod;}

Matrix mul(Matrix x,Matrix y)
{
	Matrix ret;
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
			for(int k=1;k<=cnt;++k)
				up(ret.a[i][j],x.a[i][k]*y.a[k][j]%mod);
	return ret;
}

Matrix qpow(Matrix x,int y)
{
	cerr << y << endl;
	Matrix ret;ret.Reset();
	for(;y;y>>=1,x=mul(x,x)) if(y&1) ret=mul(ret,x);
	return ret;
}

void dfs(int now,int dp,int s)
{
	if(dp==K) {sta[++cnt]=s;cerr << sta[cnt] << ' ';return;}
	for(int i=now-1;i;--i) dfs(i,dp+1,s+fc[i-1]);
}

void init()
{
	for(int i=1;i<=cnt;++i)
	{
		for(int j=1;j<=cnt;++j)
		{
			int x=(sta[i]<<1)^fc[p]^sta[j];
			if(x==lowbit(x)) 
				{cerr << i << j << endl;A.a[i][j]=1;}
		}
	}
}

int main()
{
	fc[0]=1;for(int i=1;i<20;++i) fc[i]=fc[i-1]<<1;
	scanf("%d%d%d",&n,&K,&p);
	dfs(p,1,fc[p-1]);init();
	B=qpow(A,n-K);
	cerr << B.a[1][1] << endl;
	ans.a[1][1]=1;ans=mul(ans,B);
	printf("%d\n",ans.a[1][1]);
	
	return 0;
}