#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*2;

int a[MAXN],f[MAXN],cnt[MAXN],q[MAXN];
int _head[MAXN],_next[MAXM],_node[MAXM];
int len=0,n,ans=0,fp=0,len1;
int val[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int _find(int v,int len)
{
	int l=0,r=len+1,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (q[mid]<v)
			l=mid;
		else
			r=mid;
	}
	return l;
}

void dfs(int u,int fa)
{
	int v,t1,t2,tlen1;
	a[++len]=val[u];
	t1=_find(a[len],len1);
//	cerr << a[len] << ' ' << q[t1] << endl;
	f[len]=f[t1]+1;
	t2=q[t1+1];
	q[t1+1]=a[len];
	tlen1=len1;
	len1=max(len1,t1+1);
//	for (int i=1;i<=len1;i++)
//		cerr << q[i] <<' ';
//	cerr << '\n';
	ans=max(f[len],ans);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
	}
	len--;
	q[t1+1]=t2;
	len1=tlen1;
	return ;
}

int main()
{
	freopen("2444.in","r",stdin);
	freopen("2444.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int a,b;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		_connect(a,b);
		_connect(b,a);
		cnt[a]++,cnt[b]++;
	}
	for (int i=1;i<=n;i++)
	{
		len=0;
		if (cnt[i]==1)
			dfs(i,0);
	}
	printf("%d\n",ans);
	return 0;
}