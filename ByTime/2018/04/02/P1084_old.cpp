#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

struct Ttmp{int i;long long v;};

const int MAXN = 50009,
		  MAXM = MAXN*4;

Ttmp tmp[MAXN];
int _head[MAXN],_next[MAXM],_node[MAXM],_val[MAXM];
int pos[MAXN],np[MAXN],army[MAXN];
long long r[MAXN];
int jump[MAXN][17];
long long sum[MAXN][17];
int _in[MAXN];
int n,m,c,fp=0;

bool _cmp1(Ttmp a,Ttmp b){return a.v>b.v;}
bool _cmp2(Ttmp a,Ttmp b){return a.v<b.v;}

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void pre(int u,int fa,int v)
{
	jump[u][0]=fa;
	sum[u][0]=v;
	for (int i=1;i<=16;i++)
		jump[u][i]=jump[jump[u][i-1]][i-1],
		sum[u][i]=sum[u][i-1]+sum[jump[u][i-1]][i-1];
	for (int i=_head[u];~i;i=_next[i])
		if (_node[i]!=fa)
			pre(_node[i],u,_val[i]);
	return ;
}

int up(int u,long long t,long long &left)
{
	for (int i=16;~i;i--)
	{
		if (jump[u][i]>1 && sum[u][i]<=t)
			t-=sum[u][i],u=jump[u][i];
	}
	left=(jump[u][0]==1 && t-sum[u][0]>0)?t-sum[u][0]:-1;
	return u;
}

bool dfs(int u)
{
	bool t=1,f=0;
	for (int i=_head[u];~i;i=_next[i])
		if (_node[i]!=jump[u][0])
			t&=dfs(_node[i]),f=1;
//	if (u==4)
//		cerr << t << '*' << f << endl; 
	if ((t&f)&_in[u])
	{
		tmp[c].i=army[u];
		tmp[c++].v=r[army[u]];
	}
	return _in[u]|=(t&f);
}

bool _check(long long t)
{
	c=0;
	memset(_in,0,sizeof _in);
	for (int i=1;i<=m;i++)
	{
		np[i]=up(pos[i],t,r[i]);
		if (_in[np[i]])
		{
			if (r[army[np[i]]]>r[i])
			{
				tmp[c].i=army[np[i]],
				tmp[c++].v=r[army[np[i]]];
				army[np[i]]=i;
			}
			else
			{
				tmp[c].i=i;
				tmp[c++].v=r[i];
			}
		}
		else
		{
			_in[np[i]]=1;
			army[np[i]]=i;
		}
//		cerr << up(pos[i],t,r[i]) << ' ';
	}	
//	cerr << '\n';
	dfs(1);
//	for (int i=1;i<=n;i++)
//		cerr << _in[i] << ' ';
//	cerr << '\n';
//	for (int i=0;i<c;i++)
//		cerr << tmp[i].i << ':' << tmp[i].v << ' ';
//	cerr << '\n';
	sort(tmp,tmp+c,_cmp2);
	int j=0;
	for (int i=_head[1];~i;i=_next[i])
	{
		if (_in[_node[i]])
			continue;
		while (j<c && tmp[j].v<_val[i])
			j++;
		if (j==c)
			return 0;
		j++;
	}
	return 1;
}

void _init()
{
	c=0;
	for (int i=_head[1];~i;i=_next[i])
		tmp[c].i=_node[i],tmp[c++].v=_val[i];
	sort(tmp,tmp+c,_cmp1);
	_head[1]=-1;
	for (int i=0;i<c;i++)
		_connect(1,tmp[i].i,tmp[i].v);
	pre(1,0,0);
	return ;
}

int main()
{
	freopen("P1084.in","r",stdin);
    freopen("P1084.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int a,b,v;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&v);
		_connect(a,b,v);
		_connect(b,a,v);
	}
	_init();
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
		scanf("%d",&pos[i]);
	long long l=-1,r=n*1000000000ll,mid;
	while (l+1<r)
	{
		mid=(l+r)/2ll;
		if (_check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%lld\n",r);
	return 0;
}