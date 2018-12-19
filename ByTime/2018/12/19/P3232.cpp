// Date    : 2018-12-19 14:30:30
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509,
		  MAXM = MAXN*MAXN;

const long double eps = 1e-10;

int _head[MAXN],_next[MAXM*2],_node[MAXM*2];
long double a[MAXN][MAXN],b[MAXM];
int cnt[MAXN];
int exi[MAXN][MAXN];
int n,m,tp=0,fp=0;
long double ans=0;

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

bool Gauss(long double a[MAXN][MAXN],int n)
{
	int id;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (abs(a[j][i])-abs(a[id][i])>eps)
				id=j;
		if (id!=i)
			for (int j=1;j<=n+1;j++)
				swap(a[i][j],a[id][j]);
		if (abs(a[i][i])<eps)
			return 0;
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			for (int k=n+1;k>=i;k--)
				a[j][k]-=a[i][k]*a[j][i]/a[i][i];
		}
	}
	for (int i=1;i<=n;i++)
		a[i][n+1]/=a[i][i];
	return 1;
}

inline bool _cmp(double a,double b) {return a-b>eps;}

int main()
{
//	freopen("P3232.in","r",stdin);
//	freopen("P3232.out","w",stdout);
	int x,y,v;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
		cnt[x]++,cnt[y]++;
	}
	for (int u=1;u<n;u++)
	{
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (v==n)
				continue;
			a[v][u]+=1.0/cnt[u];
		}
		a[u][u]=-1;
		a[u][n]=0;
	}
	a[1][n]=-1;
	Gauss(a,n-1);
	for (int u=1;u<n;u++)
	{
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (!exi[u][v])
				exi[u][v]=exi[v][u]=++tp;
		//	cerr << a[u][n] << endl;
			b[exi[u][v]]+=a[u][n]/cnt[u];
		}
	}
	sort(b+1,b+tp+1,_cmp);
	for (int i=1;i<=tp;i++)
		ans+=b[i]*i;
	printf("%.3lf\n",(double)ans);
	return 0;
}