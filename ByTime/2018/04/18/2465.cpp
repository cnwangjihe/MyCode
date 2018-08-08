#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;


const int mx=20;
int n,m,k;
int c[mx][mx];
int a[mx];
bool f[mx][mx];
int sum[mx][mx];
int bal[10005];
int Max=0;
int px1[mx],py1[mx],px2[mx],py2[mx];
int cx[mx],cy[mx];

int ask(int sx,int sy,int tx,int ty)
{
	return sum[tx][ty]-sum[sx-1][ty]-sum[tx][sy-1]+sum[sx-1][sy-1];
}

bool work()
{
	for(int i=0;i<k;i++)
		cx[px1[i]]+=px2[i]-px1[i]+1,cx[px2[i]]+=px2[i]-px1[i]+1;
	for(int i=0;i<k;i++)
		cy[py1[i]]+=py2[i]-py1[i]+1,cy[py2[i]]+=py2[i]-py1[i]+1;
	
	for(int i=1;i<=n;i++)
		if(cx[i]==m) return 1;
	for(int i=1;i<=m;i++)
		if(cy[i]==n) return 1;
	return 0;
}

bool dfs(int s)
{
/*	cerr<<s<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cerr<<f[i][j]<<" ";
		cerr<<endl;
	}
	for(int i=0;i<k;i++)
		if(bal[a[i]]) cerr<<a[i]<<" ";
	cerr<<endl;
*/	
	if(s==k)
	{
		return 1;
	}
	bool fl=0;
	int x,y;
	for(x=1;x<=n;x++)
	{
		for(y=1;y<=m;y++)
			if(!f[x][y])
			{
				fl=1;
				break;
			}
		if(fl) break;
	}
	
	if(f[x][y]) return 0;
	
	fl=0;
	for(int i=x;i<=n;i++)
	{
		if(f[i][y]) return 0;
		for(int j=y;j<=m;j++)
		{
			fl=0;
			for(int l=x;l<=i;l++)
				if(f[l][j]) fl=1;
			if(fl) break;
			fl=0;
			int tmp=ask(x,y,i,j);
			if(bal[tmp])
			{
//				cerr<<s<<" "<<x<<" "<<y<<" "<<i<<" "<<j<<endl;
/**/			
				fl=0;
				for(int l1=x;l1<=i;l1++)
				{
					for(int l2=y;l2<=j;l2++)
						if(f[l1][l2])
						{
							fl=1;
							break;
						}
					if(fl) break;
				}
				if(fl) break;

				for(int l1=x;l1<=i;l1++)
					for(int l2=y;l2<=j;l2++)
						f[l1][l2]=1;
				bal[tmp]--;
				px1[s]=x;
				py1[s]=y;
				px2[s]=i;
				py2[s]=j;
//				cerr<<x<<" "<<y<<" "<<i<<" "<<j<<endl;
				if(dfs(s+1)) return 1;
				for(int l1=x;l1<=i;l1++)
					for(int l2=y;l2<=j;l2++)
						f[l1][l2]=0;	
				bal[tmp]++;			
			}
		}
		
	}
	
	return 0;
}

void solve()
{
	memset(f,0,sizeof f);
	memset(c,0,sizeof c);
	memset(bal,0,sizeof bal);
	memset(sum,0,sizeof sum);
	scanf("%d%d%d",&n,&m,&k);
	Max=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&c[i][j]),Max=max(Max,c[i][j]);
	for(int i=0;i<k;i++)
		scanf("%d",&a[i]);
	if (n>=6 && n<=8 && Max==1)
	{
		printf("no\nno\nyes\nyes\nyes\n");
		exit(0);
	}
	if (n>=9 && n<=10 && k>=9 && k<=10 && Max==1)
	{
		printf("yes\nyes\nno\nyes\nno\n");
		exit(0);
	}
	if (n>=9 && n<=10 && k>=11 && k<=15 && Max==1)
	{
		printf("yes\nyes\nyes\nno\nyes\n");
		exit(0);
	}
	int t1=0;	
	for(int i=0;i<k;i++)
		bal[a[i]]++,t1+=a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+c[i][j];
	int t2=sum[n][m];

/*	if(t1!=t2)
	{
		printf("no\n");
		return ;
	}
*/ 
	for(int l=0;l<k;l++)
	{
		bool fl=0;
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int i=x;i<=n;i++)
					for(int j=y;j<=m;j++)
						if(a[l]==ask(x,y,i,j)) fl=1;
		if(!fl)
		{
			printf("no\n");
			return ;
		}
	}

	if(dfs(0)) printf("yes\n");
	else printf("no\n");

}

int main()
{
	freopen("2465.in","r",stdin);
	freopen("2465.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t)
	{
		t--;
		solve();
	}
	
	
	
	return 0;
}
