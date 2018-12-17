// Date    : 2018-12-16 22:18:44
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*4;

int _head[MAXN],_node[MAXM],_val[MAXM],_next[MAXM];
double f[MAXN];
int k[MAXN],cnt[MAXN];
int q[MAXN];
int n,m,fp=0;

void _connect(int a,int b,int c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=c;
	_head[a]=fp++;
	return ;
}

double calc()
{
	double ans=0;
	int tail=0,head=0,u,v;
	f[1]=1;
	q[tail++]=1;
	while (head!=tail)
	{
		u=q[head++];
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			f[v]+=f[u]/k[u];
			if (!--cnt[v])
				q[tail++]=v;
		}
	}
	for (int u=1;u<=n;u++)
		for (int i=_head[u];~i;i=_next[i])
			ans+=k[u]?_val[i]*f[u]/k[u]:0;
	return ans;
}

int main()
{
//	freopen("P4316.in","r",stdin);
//	freopen("P4316.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		cnt[y]++,k[x]++;
	}
	printf("%.2lf\n",calc());
	return 0;
}