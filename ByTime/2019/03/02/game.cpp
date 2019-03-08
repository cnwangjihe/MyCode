// Date      : 2019-03-02 10:41:20
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

#define count(x) __builtin_popcount(x)

const int MAXN = 21,
		  MAXM = 100009;
const long long INF = 100000000000000009ll;

char s[MAXN][MAXM];
long long A[1<<(MAXN+1)],B[1<<(MAXN+1)];
int a[MAXM];
int n,m;
long long ans=INF;

void fwt(long long a[],int n,int type)
{
	long long k=(type==-1)?2:1;
	for (int d=1;d<n;d<<=1)
		for (int m=d<<1,i=0;i<n;i+=m)
			for (int j=0;j<d;j++)
			{
				long long x=a[i+j],y=a[i+j+d];
				a[i+j]=(x+y)/k;
				a[i+j+d]=(x-y)/k;
			}
	return ;
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
	{
		int j=0;
		do {s[i][0]=getchar()^48;}
			while (s[i][0]!=0 && s[i][0]!=1);
		do {s[i][++j]=getchar()^48;}
			while (s[i][j]==0 || s[i][j]==1);
	}
	for (int j=0;j<m;j++)
		for (int i=0;i<n;i++)
			a[j]|=(s[i][j]<<i);
	for (int i=0;i<(1<<n);i++) A[i]=min(n-count(i),count(i));
	for (int i=0;i<m;i++) B[a[i]]++;
	fwt(A,(1<<n),1);
	fwt(B,(1<<n),1);
	for (int i=0;i<(1<<n);i++)
		A[i]=A[i]*B[i];
	fwt(A,(1<<n),-1);
	for (int i=0;i<(1<<n);i++)
		ans=min(ans,A[i]);
	printf("%lld\n",ans);
	return 0;
}