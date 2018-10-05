#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009;

int f[2][MAXN][MAXN];
int Min[2][MAXN][13][MAXN];
int a[MAXN][MAXN];
int lg2[MAXN];
int on,om,n,m,m0,m1;
long long ans=0;

void RMQ0(int k,int n)
{
	for (int i=1;i<=n;i++)
		Min[0][k][0][i]=f[0][i][k];
	for (int i=1;i<=m0;i++)
		for (int j=1;j<=n;j++)
			if (j+(1<<i)-1<=n)
				Min[0][k][i][j]=min(Min[0][k][i-1][j],Min[0][k][i-1][j+(1<<(i-1))]);
	return ;
}

void RMQ1(int k,int n)
{
	for (int i=1;i<=n;i++)
		Min[1][k][0][i]=f[1][k][i];
	for (int i=1;i<=m1;i++)
		for (int j=1;j<=n;j++)
			if (j+(1<<i)-1<=n)
				Min[1][k][i][j]=min(Min[1][k][i-1][j],Min[1][k][i-1][j+(1<<(i-1))]);
	return ;
}

int query0(int l,int r,int k)
{
	int len=lg2[r-l+1];
	return min(Min[0][k][len][l],Min[0][k][len][r-(1<<len)+1]);
}

int query1(int l,int r,int k)
{
	int len=lg2[r-l+1];
	return min(Min[1][k][len][l],Min[1][k][len][r-(1<<len)+1]);
}

bool check(int x,int y,int len)
{
	if (x-len<=0 || x+len>=n-1 || y-len<=0 || y+len>=m-1)
		return 0;
	if (min(query0(x-len,x+len,y),query1(y-len,y+len,x))>=len)
		return 1;
	return 0;
}

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+(c^48);
	return x;
}

int main()
{
	lg2[1]=0;
	for (int i=2;i<2005;i++)
		lg2[i]=lg2[i/2]+1;
	freopen("hard.in","r",stdin);
	freopen("hard.out","w",stdout);
	on=read(),om=read();
	for (int i=1;i<=on;i++)
		for (int j=1;j<=om;j++)
			a[i*2][j*2]=read();
	n=on*2+3,m=om*2+3;
	for (int i=0;i<n;i++)
		a[i][m-1]=30,a[i][0]=31;
	for (int i=0;i<m;i++)
		a[n-1][i]=32,a[0][i]=33;
	int p;
	for (int j=1;j<n-1;j++)
	{
		p=2;
		f[0][j][2]=1;
		f[0][j][0]=f[0][j][1]=0;
		for (int i=3;i<m-1;i++)
		{
			f[0][j][i]=max(0,min(f[0][j][2*p-i],p+f[0][j][p]-i));
			while (a[j][i-f[0][j][i]-1]==a[j][i+f[0][j][i]+1])
				f[0][j][i]++;
			if (p+f[0][j][p]<i+f[0][j][i])
				p=i;
		}
	}
	for (int j=1;j<m-1;j++)
	{
		p=2;
		f[1][2][j]=1;
		f[1][0][j]=f[1][1][j]=0;
		for (int i=3;i<n-1;i++)
		{
			f[1][i][j]=max(0,min(f[1][2*p-i][j],p+f[1][p][j]-i));
			while (a[i-f[1][i][j]-1][j]==a[i+f[1][i][j]+1][j])
				f[1][i][j]++;
			if (p+f[1][p][j]<i+f[1][i][j])
				p=i;
		}
	}
/*
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
			cerr << a[i][j] << ' ';
		cerr << '\n';
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
			cerr << f[0][i][j] << ' ';
		cerr << '\n';
	}
	cerr << '\n';
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
			cerr << f[1][i][j] << ' ';
		cerr << '\n';
	}
*/
	m0=(int)log2(n-2);
	m1=(int)log2(m-2);
	for (int i=1;i<m-1;i++)
		RMQ0(i,n-2);
	for (int i=1;i<n-1;i++)
		RMQ1(i,m-2);
//	cerr << query0(1,3,10) << ' ' << query1(9,10,2) << ' ' << query1(10,11,2) << ' ' << query1(9,11,2) << endl;
//	cerr << Min[1][2][1][9] << ' ' << Min[1][2][0][10]  << ' ' << Min[1][2][0][11] << '\n';
//	cerr << m0 << ' ' << m1 << endl;
	int l,r,mid;
	for (int i=1;i<n-1;i++)
		for (int j=1;j<m-1;j++)
		{
			if ((i&1)^(j&1))
				continue;
			l=0,r=min(on,om)+1;
			while (l+1<r)
			{
				mid=(l+r)/2;
				if (check(i,j,mid))
					l=mid;
				else
					r=mid;
			}
//			cerr << i << ' ' << j << ' ' << a[i][j] << ' ' << l << '\n';
			ans+=(1ll*l+1ll)/2ll;
		}
	printf("%lld\n",ans);
	return 0;
}
