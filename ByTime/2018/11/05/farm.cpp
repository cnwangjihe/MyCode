#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20009;

int _head[MAXN],_node[MAXN*2],_val[MAXN*2],_next[MAXN*2];
int dis[MAXN],cnt[MAXN];
bool _in[MAXN];
int n,m,fp=0;
stack<int> line;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

bool SPFA()
{
	int u,v;
	for (int i=1;i<=n;i++)
	{
		line.push(i);
		cnt[i]=_in[i]=1;
		dis[i]=0;
	}
	while (!line.empty())
	{
		u=line.top();
		line.pop();
	//	cerr << u << endl;
		_in[u]=0;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (dis[u]+_val[i]<dis[v])
			{
				dis[v]=dis[u]+_val[i];
				if (++cnt[v]>n)
					return 0;
				if (!_in[v])
					line.push(v),_in[v]=1;
			}
		}
	}
	return 1;
}

int main()
{
	freopen("farm.in","r",stdin);
	freopen("farm.out","w",stdout);

	memset(_head,-1,sizeof _head);
	int t,x,y;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		t=read(),x=read(),y=read();
		if (t==1)
			_connect(x,y,-read());
		if (t==2)
			_connect(y,x,read());
		if (t==3)
			_connect(x,y,0),_connect(y,x,0);
	}
	printf("%s\n",SPFA()?"Yes":"No");
	return 0;
}