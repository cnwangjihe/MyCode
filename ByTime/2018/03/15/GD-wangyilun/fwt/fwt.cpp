#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1030,
		  MAXM = MAXN*2;
const long long MOD = 1000000007ll;

int _head[MAXN],_next[MAXM],_node[MAXM];
long long f[MAXN][MAXN],tmp[MAXN];
int cnt[MAXN],a[MAXN],val[MAXN][MAXN];
bool vis[MAXN][MAXN];
int fp=0,n,m;
int t1,t2,t3,koi=0;
long long ans;

void clean()
{
	memset(_head,-1,sizeof _head);
	memset(f,0,sizeof f);
	memset(vis,0,sizeof vis);
	fp=0;
}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u, int fa)
{
	int v;
	cnt[u]=0;
	f[u][a[u]]=1;
	val[u][cnt[u]++]=a[u];
	vis[u][a[u]]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
//		cerr << u << ' ' << v << endl;
		dfs(v,u);
		memset(tmp,0,sizeof tmp);
		for (int j=cnt[u]-1;j>=0;j--)
		{
			for (int k=0;k<cnt[v];k++)
			{
				t1=val[u][j],t2=val[v][k],t3=t1^t2;
				tmp[t3]+=(f[u][t1]*f[v][t2])%MOD;
				tmp[t3]%=MOD;
				if (!vis[u][t3])
				{
					val[u][cnt[u]++]=t3;
					vis[u][t3]=1;
				}
//				koi++;
			}
		}
		for (int j=0;j<m;j++)
			f[u][j]+=tmp[j],f[u][j]%=MOD;
	}
	return ;
}

int main()
{
	freopen("fwt.in","r",stdin);
	freopen("fwt.out","w",stdout);
	int ttt,x,y;
	scanf("%d",&ttt);
//	cerr << ttt; 
	while (ttt--)
	{
		scanf("%d%d",&n,&m);
		clean();
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=0;i<n-1;i++)
		{
			scanf("%d%d",&x,&y);
			_connect(x,y);
			_connect(y,x);
		}
		dfs(1,0);
		for (int i=0;i<m;i++)
		{
			ans=0ll;
			for (int j=1;j<=n;j++)
				ans+=f[j][i],ans%=MOD;
			printf("%I64d ",ans);
		}
		putchar('\n');
//		cerr << koi << endl;
	}
	return 0;
}