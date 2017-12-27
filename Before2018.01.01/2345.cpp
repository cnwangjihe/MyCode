#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <queue>

using namespace std;

const int MAXN = 200006;

struct Tnode
{
	int low,top,i;
	bool operator < (const Tnode &t) const {return top>t.top;}
}a[MAXN];

int head[2][MAXN],cnt[2][MAXN];
int _next[MAXN*2],node[MAXN*2];
int line[MAXN];
int ans[MAXN];
int n,m,k,fp=0;

bool _cmp(Tnode A,Tnode B) {return A.low<B.low;}

void _add(int x,int y,int k)
{
	_next[fp]=head[k][x];
	node[fp]=y;
	head[k][x]=fp++;
}

bool _init(int t)
{
	int he=0,ta=0,u,v;
	for(int i=1;i<=n;i++)
		if(!cnt[t][i]) line[ta++]=i;
	
	while(he<ta)
	{
		u=line[he++];
		for(int i=head[t][u];i!=-1;i=_next[i])
		{
			v=node[i]; cnt[t][v]--;
			if (t) a[v].top=min(a[v].top,a[u].top-1);
				else a[v].low=max(a[v].low,a[u].low+1);
			if(!cnt[t][v]) line[ta++]=v;
		}
	}
	if (ta<n) return 1;
	return 0;
}

bool solve()
{
	Tnode tmp;
	int j=1;
	priority_queue<Tnode> q;
	bool flag;
	for(int i=1;i<=k;i++)
	{
		flag=0;
		for(;j<=n && a[j].low==i;j++) 
		{
			tmp=a[j];tmp.i=j;
			q.push(tmp);
		}
		while(!q.empty() && q.top().top==i) 
		{
			tmp=q.top();q.pop();
			ans[a[tmp.i].i]=i;
			flag=true;
		}
		if(!flag)
		{
			if(q.empty()) return 1;
			tmp=q.top();q.pop();
			ans[a[tmp.i].i]=i;
		}
	}
	return 0;
}

bool check()
{
	for(int i=1;i<=n;i++) 
		if(a[i].top<a[i].low) return 1;
	return 0;
}

int main()
{
	memset(head,-1,sizeof head);
	int x,y;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a[i].i=i;
		if(x) a[i].top=x,a[i].low=x;
			else a[i].top=k,a[i].low=1;
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_add(y,x,0);
		_add(x,y,1);
		cnt[0][x]++;
		cnt[1][y]++;
	}
	if (_init(0) || _init(1)) return 0&printf("-1\n");
	sort(a+1,a+n+1,_cmp);
	if (check() || solve()) printf("-1\n");
		else 
			for (int i=1;i<=n;i++) 
				printf("%d ",ans[i]);
	return 0;
}
