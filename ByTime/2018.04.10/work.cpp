#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int n,m,e,k,q;
bool mp[109][109],f[109][109];
int x[2009],y[2009];
int nU,nL,nR,nD,ans,sum;
char c;

inline void read(int &x)
{  
	x=0;char c=getchar();  
	while(c<'0' || c>'9')c=getchar();  
	while(c>='0' && c<='9')
	{  
		x=x*10+c-'0';  
		c=getchar();  
	}   
	return ;
}
inline void readc(char &x)
{
	do {x=getchar();}
		while (x!='R' && x!='L' && x!='D' && x!='U');
	return ;
}

inline void write(int x)
{  
	if(x==0){putchar(48);return;}  
	int len=0,dg[20];  
	while(x>0){dg[++len]=x%10;x/=10;}  
	for(int i=len;i>=1;i--)putchar(dg[i]+48);  
}

int main()
{
	freopen("work.in","r",stdin);
	freopen("work.out","w",stdout);
	read(n);read(m);read(e);read(q);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			mp[i][j]=1;
	sum=n*m-e;
	for (int i=0;i<e;i++)
		read(x[i]),read(y[i]),mp[x[i]][y[i]]=0;
	nL=1,nR=m,nU=1,nD=n;
	for (int i=0;i<q;i++)
	{
		readc(c);read(k);
		memset(f,0,sizeof f);
		ans=0;
		if (!sum)
		{
			printf("0\n");
			continue;
		}
		if (c=='U')
		{
			nU+=k;
			nD+=k;
			for (int j=1;j<nD;j++)
				for (int p=1;p<=m;p++)
					ans+=mp[j][p],mp[j][p]=0;
		//	cerr << ans << '\n';
			for (int j=0;j<e;j++)
			{
				int ty=y[j];
				for (int tx=max(1,x[j]+1);tx<=n && tx-x[j]<=k && !f[tx][ty];tx++)
					ans+=mp[tx][ty],mp[tx][ty]=0,f[tx][ty]=1;
				x[j]=x[j]+k;
			}
		}
		if (c=='D')
		{
			nD-=k;
			nU-=k;
			for (int j=nD+1;j<=n;j++)
				for (int p=1;p<=m;p++)
					ans+=mp[j][p],mp[j][p]=0;
		//	cerr << ans << '\n';
			for (int j=0;j<e;j++)
			{
				int ty=y[j];
				for (int tx=min(n,x[j]-1);tx>0 && x[j]-tx<=k && !f[tx][ty];tx--)
					ans+=mp[tx][ty],mp[tx][ty]=0,f[tx][ty]=1;
				x[j]=x[j]-k;
			}
		}
		if (c=='L')
		{
			nL+=k;
			nR+=k;
			for (int j=1;j<nL;j++)
				for (int p=1;p<=n;p++)
					ans+=mp[p][j],mp[p][j]=0;
		//	cerr << ans << '\n';
			for (int j=0;j<e;j++)
			{
				int tx=x[j];
				for (int ty=max(1,y[j]+1);ty<=m && ty-y[j]<=k && !f[tx][ty];ty++)
					ans+=mp[tx][ty],mp[tx][ty]=0,f[tx][ty]=1;
				y[j]=y[j]+k;
			}
		}
		if (c=='R')
		{
			nR-=k;
			nL-=k;
			for (int j=nR+1;j<=m;j++)
				for (int p=1;p<=n;p++)
					ans+=mp[p][j],mp[p][j]=0;
		//	cerr << ans << '\n';
			for (int j=0;j<e;j++)
			{
				int tx=x[j];
				for (int ty=min(m,y[j]-1);ty>0 && y[j]-ty<=k && !f[tx][ty];ty--)
					ans+=mp[tx][ty],mp[tx][ty]=0,f[tx][ty]=1;
				y[j]=y[j]-k;
			}
		}
		sum-=ans;
		printf("%d\n",ans);
	}
	return 0;
}