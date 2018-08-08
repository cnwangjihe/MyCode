#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 100009;

struct Tnode {int u;long long v;};

int _head[MAXN],_next[MAXM],_node[MAXM];
int fa[MAXN],a[MAXN];
bool f[MAXN];
int n,m,k,fp;
long long sum;
long long ans[MAXN],c[MAXN];
Tnode leaf[MAXN];

bool _cmp(Tnode a,Tnode b) {return a.v<b.v;}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}
void dfs(int u)
{
//	cerr << c[u] << ' ';
	if (!(~_head[u]))
	{
		leaf[m].u=u;
		leaf[m++].v=c[u];
		return ;
	}
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		c[v]=c[u]+a[v];
		dfs(v);
	}
	return ;
}

void _reset()
{
	memset(_head,-1,sizeof _head);
	memset(f,0,sizeof f);
	memset(fa,0,sizeof fa);
	memset(ans,0,sizeof ans);
	f[0]=1;
	m=fp=0;
	sum=0;
}

int main()
{
	int ttt,x,y;
	scanf("%d",&ttt);
	for (int tt=1;tt<=ttt;tt++)
	{
		_reset();
		scanf("%d%d",&n,&k);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
	//		cerr << x << ' ' << y << '\n';
			_connect(x,y);
			fa[y]=x;
		}
		c[1]=a[1];
		dfs(1);
	//	cerr << m << '\n'; 
		sort(leaf,leaf+m,_cmp);
		for (int i=m-1;~i;i--)
		{
			for (int j=leaf[i].u;!f[j];f[j]=1,j=fa[j])
				ans[i]+=(long long)a[j];
	//		cerr << leaf[i].v << endl;
		}
		sort(ans,ans+m);
		for (int i=m-1;i>=m-k;i--)
			sum+=ans[i];
		printf("Case #%d: %I64d\n",tt,sum);
	}
	return 0;
}
