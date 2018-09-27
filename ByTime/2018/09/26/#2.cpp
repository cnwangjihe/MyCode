#include<bits/stdc++.h>

using namespace std ;

const int N=1e5+10;
const int M=18;
int a[N],rmq[M][N],f[N],g[N],lg2[N],n,m;

int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())x=x*10+(c^48);
	return x;
}

int getmax(int l,int r)
{
	if (l>r) return 0;
	int d=lg2[r-l+1];
	return (a[rmq[d][l]]>=a[rmq[d][r-(1<<d)+1]])?rmq[d][l]:rmq[d][r-(1<<d)+1];
}

void solve()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++) rmq[0][i]=i;
	for (int i=1;i<M;i++) 
		for (int j=1;j<=n-(1<<i)+1;j++)
			rmq[i][j]=(a[rmq[i-1][j]]>=a[rmq[i-1][j+(1<<i-1)]])?rmq[i-1][j]:rmq[i-1][j+(1<<i-1)];
	f[1]=1;
	for (int i=2;i<=n;i++)
	{
		int pre=getmax(1,i-1);
		if (a[i]> a[pre])	f[i]=f[pre]+1;	else
		if (a[i]==a[pre])	f[i]=f[pre];	else
							f[i]=0;
	}
	g[n]=1;
	for (int i=n-1;i>=1;i--)
	{
		int nxt=getmax(i+1,n);
		if (a[i]< a[nxt])	g[i]=g[nxt]+1;	else
		if (a[i]==a[nxt])	g[i]=g[nxt];	else
							g[i]=0;
	}
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read(),ans=0;
		int pre=getmax(1,x-1);
		int l=x+1,r=n+1;
		while (l<r)
		{
			int mid=l+r>>1,v=getmax(x+1,mid);
			if (mid==n+1) {l=mid;break;}
			if (v>y) r=mid; else l=mid+1;
		}
		if (r!=n+1)		ans+=g[r];
		if (x!=1)
		{
			if (x>a[pre])	ans+=f[pre]+1;
				else		ans+=f[pre];
		}
		else ans++;
		printf("%d\n",ans);
	}
}

int main()
{
	int st=clock();
	freopen("a.in","r",stdin);
//	freopen("#2.out","w",stdout);
	
	for (int i=2;i<N;i++) 
		lg2[i]=lg2[i/2]+1;
	int T=read();
	for(;T;T--)solve();
	cerr << "time: "<< clock()-st << endl;
	return 0;
}
