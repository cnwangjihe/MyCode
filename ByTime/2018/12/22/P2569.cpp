// Date    : 2018-12-22 08:23:21
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

const int MAXN = 2009,
		  INF  = 1000000007;

#define cerr std::cerr
#define mkp std::make_pair
template <class T> inline void swap(T &a,T &b) {T c(a);a=b,b=c;}
template <class T> inline T max(T a,T b) {return a>b?a:b;}

int ap[MAXN],bp[MAXN],as[MAXN],bs[MAXN];
std::pair<int,int> q[MAXN];
int f[MAXN][MAXN];
int head,tail;
int n,m,w;

int main()
{
//	freopen("P2569.in","r",stdin);
//	freopen("P2569.out","w",stdout);
	int t;
	scanf("%d%d%d",&n,&m,&w);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			f[i][j]=-INF;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=m;j++)
		{
			if (j<=as[i])
				f[i][j]=max(f[i][j],-j*ap[i]);
			if (i-1)
				f[i][j]=max(f[i][j],f[i-1][j]);
		}
		if (i-w-1<=0)
			continue;
		head=0,tail=-1;
		for (int j=0;j<=m;j++)
		{
			while (head<=tail && q[head].first<j-as[i])
				head++;
			if (head<=tail)
				f[i][j]=max(f[i][j],q[head].second-j*ap[i]);
			t=f[i-w-1][j]+j*ap[i];
			while (head<=tail && q[tail].second<=t)
				tail--;
			q[++tail]=mkp(j,t);
		}
		head=0,tail=-1;
		for (int j=m;~j;j--)
		{
			while (head<=tail && q[head].first>j+bs[i])
				head++;
			if (head<=tail)
				f[i][j]=max(f[i][j],q[head].second-j*bp[i]);
			t=f[i-w-1][j]+j*bp[i];
			while (head<=tail && q[tail].second<=t)
				tail--;
			q[++tail]=mkp(j,t);
		}
	}
	printf("%d\n",f[n][0]);
	return 0;
}