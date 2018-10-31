#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009,
		  MAXM = 200009,
		  INF  = 1000000009;

int _head[MAXN],_node[MAXM],_val[MAXM],_next[MAXM];
int f[MAXM];
int n,m,fp=0,ans;

priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void SPFA(int st)
{
	int u,e,t,w;
	for (;!q.empty();q.pop());
	q.push(make_pair(0,st));
	while (!q.empty())
	{
		e=q.top().second;
		u=_node[e];
		w=q.top().first;
		q.pop();
		if (f[e]!=w)
			continue;
		for (int i=_head[u];~i;i=_next[i])
		{
			t=(_val[i]!=_val[e]);
			if (f[i]<=f[e]+t)
				continue;
			f[i]=f[e]+t;
			q.push(make_pair(f[i],i));
		}
	}
	return ;
}

int main()
{
	freopen("2688.in","r",stdin);
	freopen("2688.out","w",stdout);
	int x,y,z;
	while (scanf("%d%d",&n,&m)==2 && (n || m))
	{
		ans=INF;
		memset(_head,-1,sizeof _head);
		fp=0;
		for (int i=0;i<m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			_connect(x,y,z);
			_connect(y,x,z);
		}
		for (int i=0;i<fp;i++)
			f[i]=INF;
		_connect(0,1,0);
		f[fp-1]=0;
		SPFA(fp-1);
		for (int i=0;i<fp-1;i++)
			if (_node[i]==n)
			{
			//	cerr << i << ' ' << f[i] << endl;
				ans=min(ans,f[i]);
			}
		printf("%d\n",ans==INF?-1:ans);
	}
	return 0;
}