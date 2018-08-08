#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <iostream>

using namespace std;

const int MAXN = 52,
		  MAXM = MAXN*MAXN*2,
		  MAXNF = 22,
		  MOD  = 10000;

struct TMatrix
{
	int v[MAXN][MAXN],n;
	void Clear() {memset(v,0,sizeof v);}
	void Reset() {Clear();for (int i=0;i<n;i++) v[i][i]=1;}
	TMatrix(){n=MAXN;Clear();}
	TMatrix operator *(const TMatrix &a)
	{
		TMatrix ans;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				for (int k=0;k<n;k++)
					ans.v[i][j] += (v[i][k] * a.v[k][j]) % MOD,
					ans.v[i][j] %= MOD;
		return ans;
	}
	TMatrix operator *=(const TMatrix &a)
	{
		*this=*this*a;
		return *this;
	}
};

int _node[MAXM],_next[MAXM],_head[MAXN],fp=0;
int n,m,k,times,st,en,nfish;
int mp[MAXNF][5];
int c[MAXNF];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void _out(TMatrix tmp)
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
			cerr << tmp.v[i][j] << ' ';
		cerr << '\n';
	}
	cerr << "---------------------\n";
	return ;
}

int main()
{
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int u,v;
	scanf("%d%d%d%d%d",&n,&m,&st,&en,&k);
	TMatrix mt[13];
	times=k/12;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&u,&v);
		_connect(u,v);
		_connect(v,u);
	}
	scanf("%d",&nfish);
	for (int i=0;i<nfish;i++)
	{
		scanf("%d",&c[i]);
		for (int j=0;j<c[i];j++)
			scanf("%d",&mp[i][j]);
	}
	for (int u=0;u<n;u++)
		for (int i=_head[u];~i;i=_next[i])
			for (int j=1;j<13;j++)
				mt[j].v[u][_node[i]]=1;
	for (int u=0;u<nfish;u++)
		for (int i=1;i<13;i++)
		{
			for (int j=0;j<n;j++)
				mt[i].v[j][mp[u][i%c[u]]]=0;
	//		_out(mt[i]);
		}
	TMatrix ansmt,a;
	a.Reset(),ansmt.Reset();
	for (int i=1;i<13;++i)
		a*=mt[i];
	for (int i=0;(1<<i)<=times;i++,a*=a)
		if ((1<<i)&times)
			ansmt*=a;
	for (int i=1;i<=k-times*12;i++)
		ansmt*=mt[i];
	printf("%d\n",ansmt.v[st][en]);
	return 0;
}