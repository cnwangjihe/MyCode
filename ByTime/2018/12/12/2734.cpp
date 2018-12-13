// Date    : 2018-12-12 20:56:52
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30;

struct Tenv{int c,t,v,p;};

Tenv a[MAXN];
bool vis[MAXN];
int n,m,fp=0;
double napp[MAXN];
double ans,zero;
int k[MAXN];

bool _cmp(Tenv A,Tenv B){return A.v>B.v;}

void dfs(int i,double k,int c,int sum)
{
	if (c==n || i==fp)
	{
		ans=max(ans,k*sum);
	//	cerr << k << " " << sum << '\n';
		return ;
	}
	if (!vis[a[i].c])
	{
		vis[a[i].c]=1;
		dfs(i+1,k/napp[a[i].c]*a[i].p/100,c+1,sum+a[i].v);
		vis[a[i].c]=0;
	}
	dfs(i+1,k,c,sum);
	return ;
}

int main()
{
	freopen("2734.in","r",stdin);
	freopen("2734.out","w",stdout);
	int T;
	int sp;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		fp=0;
		zero=1;
		scanf("%d%d",&n,&m);
		for (int i=0;i<m;i++)
		{
			scanf("%d",&k[i]);
			sp=0;
			for (int j=0;j<k[i];j++)
			{
				scanf("%d%d%d",&a[fp].t,&a[fp].v,&a[fp].p);
				a[fp].c=i;
				sp+=a[fp].p;
				fp++;
			}
			if (sp!=100)
			{
				napp[i]=1.0-sp/100.0;
				zero*=napp[i];
			}
			else
			{
				napp[i]=1;
			}
		}
		sort(a,a+fp,_cmp);
		dfs(0,zero,0,0);
		printf("%.6lf\n",ans);
	}

	return 0;
}