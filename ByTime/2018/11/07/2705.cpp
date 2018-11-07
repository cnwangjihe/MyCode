#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005,
		  MAXM = 205,
		  MAXK = 200005;

const long long INF=1000000010ll;

struct Tnode{int x,y;};

int n,m,k;
Tnode a[MAXK];
int w[MAXN][MAXM];
long long f[MAXN*2][MAXN*2],s[MAXN][MAXM];
long long sum[MAXN];

inline int read()
{
	char c=0;
	int w=0,x=0;
	while(!isdigit(c))
		w|=(c=='-'),c=getchar();
	while(isdigit(c))
		x=x*10+c-'0',c=getchar();
	return w?-x:x;
}

void floyd()
{
	for(int i=1;i<=n+n;i++)
		for(int j=1;j<=n+n;j++)
			f[i][j]=INF;
	for(int i=1;i<=n;i++)
		f[i][i+n]=sum[i]-w[i][1],f[i+n][i]=sum[i]-w[i][m],f[i][i]=f[i+n][i+n]=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=1) f[i-1][i]=w[i][1],f[i+n-1][i+n]=w[i][m];
		if(i!=n) f[i+1][i]=w[i][1],f[i+n+1][i+n]=w[i][m];
	}
	for(int k=1;k<=n+n;k++)
		for(int i=1;i<=n+n;i++)
			for(int j=1;j<=n+n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]); 
}

long long sdis(int sx,int sy,int tx,int ty)
{
	long long sl=s[sx][sy]-w[sx][sy],sr=sum[sx]-s[sx][sy];
	long long tl=s[tx][ty]-w[tx][1],tr=sum[tx]-s[tx][ty]+w[tx][ty]-w[tx][m];
	return min(min(sl+f[sx][tx]+tl,sl+f[sx][tx+n]+tr),min(sr+f[sx+n][tx]+tl,sr+f[sx+n][tx+n]+tr));
}

int main()
{
	freopen("2705.in","r",stdin);
	freopen("2705.out","w",stdout);
	
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			w[i][j]=read();
	k=read();
	for(int i=0;i<k;i++)
		a[i].x=read(),a[i].y=read();

	for(int i=1;i<=n;i++)
	{
		sum[i]=0; s[i][0]=0;
		for(int j=1;j<=m;j++)
			sum[i]+=w[i][j],s[i][j]=s[i][j-1]+w[i][j];
	}
	floyd();
	
	int x=1,y=1;
	long long ans=w[1][1];
	for(int i=0;i<k;i++)
	{
		ans+=sdis(x,y,a[i].x,a[i].y);
//		cerr<<x<<" "<<y<<" "<<a[i].x<<" "<<a[i].y<<" "<<sdis(x,y,a[i].x,a[i].y)<<endl;
		x=a[i].x,y=a[i].y;
	}
	printf("%lld\n",ans);
	return 0;
}
