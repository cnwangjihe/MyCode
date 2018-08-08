#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5000000,
		  MOD  = 1333331,
		  MAXH = 5000000;

struct Tdata{long long phi,miu;};
const struct Tdata dnull={-1,-1};
struct Thash
{
	int id[MAXH],_head[MOD],_next[MAXH];
	Tdata v[MAXH];
	int fp;
	Thash(){memset(_head,-1,sizeof _head);fp=0;}
	void push(int k,Tdata a)
	{
		int u=k%MOD;
		for (int i=_head[u];~i;i=_next[i])
			if (id[i]==k)
			{
				cerr << "WARNING : HASH PROGRAM WRONG";
				return ;
			}
		_next[fp]=_head[u];
		v[fp]=a;
		id[fp]=k;
		_head[u]=fp++;
		return ;
	}
	Tdata pull(int k)
	{
		int u=k%MOD,i;
		for (i=_head[u];(~i) && id[i]!=k;i=_next[i]);
		return ((~i)?v[i]:dnull);
	}
};

Tdata g[MAXV];
Thash Hash;
bool vis[MAXV];
int p[MAXV/7];
int m=0;

void init()
{
	int tmp;
	g[1].phi=1,g[1].miu=1;
	for (int i=2;i<MAXV;i++)
	{
		if (!vis[i])
		{
			p[m++]=i;
			g[i].phi=i-1;
			g[i].miu=-1;
		}
	//	cerr << i << endl;
		for (int j=0;j<m && 1LL*p[j]*i<MAXV;j++)
		{
			tmp=i*p[j];
			vis[tmp]=1;
			if (i%p[j]==0)
			{
				g[tmp].phi=g[i].phi*p[j];
				g[tmp].miu=0;
				break;
			}
			g[tmp].phi=g[i].phi*g[p[j]].phi;
			g[tmp].miu=g[i].miu*g[p[j]].miu;
		}
	}
	for (int i=2;i<MAXV;i++)
		g[i].phi+=g[i-1].phi,g[i].miu+=g[i-1].miu;
	return ;
}

Tdata calc(int n)
{
	if (n<MAXV)
		return g[n];
	Tdata v=Hash.pull(n),t;
	if (v.phi!=-1)
		return v;
	int j;
	v.phi=(long long)n*(n+1ll)/2ll;
	v.miu=1ll;
	for (int i=2;i<=n;i=j+1)
	{
		j=n/((int)n/i);
		t=calc(n/i);
		v.phi-=(long long)(j-i+1)*t.phi;
		v.miu-=(long long)(j-i+1)*t.miu;
	}
	Hash.push(n,v);
	return v;
}

int main()
{
	int ttt,n;
	Tdata ans;
	init();
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		ans=calc(n);
		printf("%lld %lld\n",ans.phi,ans.miu);
	}
	return 0;
}