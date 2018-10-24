#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8890,
		  MAXM = 200009;

int b[MAXN],d[MAXN],l[MAXN];
int p[MAXN],q[MAXN],s[MAXN],vis[MAXN];
int _head[MAXN],_next[200009],_node[200009];
bool f[MAXN][MAXN];
int top=0,c=0,tim=0,fp=0,n;

void tarjan(int u)
{
	int y,v;
	d[u]=l[u]=++tim;
	vis[u]=1;
	s[top++]=u;

	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (!d[v])
		{
			tarjan(v);
			l[u]=min(l[u],l[v]);
		}
		else
		{
			if (vis[v])
				l[u]=min(l[u],d[v]);
		}
	}
	if (d[u]==l[u])
	{
		c++;
		do {y=s[--top],vis[y]=0,b[y]=c;}
			while (u!=y);
	}
	return ;
}

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
	return x*f;
}

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int main()
{
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,v;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (;x=read();_connect(i,x));
	for (int i=1;i<=n;i++)
		if (!d[i])
			tarjan(i);
	for (int i=1;i<=n;i++)
	{
		for (int j=_head[i];~j;j=_next[j])
		{
			v=_node[j];
			if (b[i]!=b[v])
				f[b[i]][b[v]]=1;
		}
	}
	for (int i=1;i<=c;i++)
		for (int j=1;j<=c;j++)
			if (f[i][j])
				p[i]++,q[j]++;
	x=y=0;
	for (int i=1;i<=c;i++)
		x+=p[i]?0:1,y+=q[i]?0:1;
	printf("%d\n%d\n",y,max(x,y));
	return 0;
}
