#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007ll;
const int MAXK = 200;

LL f[MAXK][MAXK][MAXK];
LL g[2][MAXK][3];
int k1,k2,K,ccnntt;
int h[2];
LL a,b,c,x,y,z;

void gofa(LL &a,LL &b,LL &c)
{
	LL tmp;
	if (b-a<c-b)
		tmp=b+b-a,a=b,b=tmp;
	else
	if (b-a>c-b)
		tmp=b+b-c,c=b,b=tmp;
	return ;
}

int jump(LL a,LL b,LL c,int K,bool t)
{
	int i=0;
	for (i=0;i<=K;i++)
	{
	//	cerr << a << ' ' <<b << ' ' << c << endl;
		g[t][i][0]=a;
		g[t][i][1]=b;
		g[t][i][2]=c;
		if (b-a==c-b)
		{
			i++;
			break;
		}
		gofa(a,b,c);
	}
	return i-1;
}

void GetLCA(LL a,LL b,LL c,LL x,LL y,LL z)
{
	k1=jump(a,b,c,K,0);
	k2=jump(x,y,z,K,1);
	int Min=100000000;
	for (int i=0;i<=k1;i++)
		for (int j=0;j<=k2;j++)
			if (g[0][i][0]==g[1][j][0] && g[0][i][1]==g[1][j][1] && g[0][i][2]==g[1][j][2])
			{
				if (i+j<Min)
					Min=i+j,h[0]=i,h[1]=j;
			}
	return ;
}

LL dfs(int i,int j,int k)
{
//	cerr << i <<' ' << j << ' ' << k << '\n';
//	ccnntt++;
	if (~f[i][j][k])
		return f[i][j][k];
	f[i][j][k]=0;
	if (i==j&&j==k&&k==0)
	{
		f[i][j][k] = 1;
		return 1;
	}
	if (i+j>k)
		return 0;
	if ((!i) && j>k2)
		return 0;
	if ((!i) && (!j) && k>0)
		f[i][j][k]=(dfs(0,1,k-1)+dfs(1,0,k-1)+dfs(1,0,k-1))%MOD;
	if ((!i) && j>0)
		f[i][j][k]=(dfs(0,j-1,k-1)+dfs(1,j,k-1)+dfs(0,j+1,k-1))%MOD;
	if (i)
		f[i][j][k]=(dfs(i-1,j,k-1)+dfs(i+1,j,k-1)+dfs(i+1,j,k-1))%MOD;
//	if (f[i][j][k]) cerr << "sdfs";
	return f[i][j][k];
}

int main()
{
	ccnntt=0;
	freopen("rabbits.in","r",stdin);
	freopen("rabbits.out","w",stdout);
	scanf("%I64d%I64d%I64d",&a,&b,&c);
	scanf("%I64d%I64d%I64d",&x,&y,&z);
	memset(f,-1,sizeof f);
	scanf("%d",&K);
	GetLCA(a,b,c,x,y,z);
//	return 0;
	f[0][0][0]=1;
//	cerr << h[0] << ' ' << h[1] << '\n';
//	printf("%d%d%d\n",h[0],h[1],K);
	printf("%I64d\n",dfs(h[0],h[1],K));
	return 0;
}
