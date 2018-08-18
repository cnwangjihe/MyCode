#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2019;

int _head[MAXN],_next[MAXN],_node[MAXN],_val[MAXN];
int c[MAXN],d[MAXN],ans[MAXN],k[MAXN];
int q[MAXN];
int f[MAXN][MAXN];
int n,fp=0;

int ask(int x)
{
	for (int i=0;i<d[x];i++)
	{
		if (f[x][i]>=(c[x]+1)/2)
			return i;
	}
	return d[x];
}

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void bfs()
{
	int head=0,tail=0,u,v;
	for(int i=1;i<=n;i++)
	{
		if(k[i]==0)
			q[tail++]=i;
	}
    while (head!=tail)
    {
        u=q[head++];
        d[u]=ask(u);
        for (int j=_head[u];~j;j=_next[j])
        {
            v=_node[j];
            if (d[v]>d[u])
            {
                for (int i=d[v]-d[u];i>=0;i--)
                    f[v][i+d[u]]=max(f[v][i+d[u]],f[v][i]+_val[j]); 
            }
            k[v]--;
            if (k[v]==0)
            	q[tail++]=v;
        }
    }
	return ;
}

int main()
{
	freopen("2635.in","r",stdin);
	freopen("2635.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&c[i],&d[i],&k[i]);
		for (int j=0;j<k[i];j++)
		{
			scanf("%d%d",&x,&y);
			_connect(x,i,y);
		}
	}
	bfs();
	for (int i=1;i<=n;i++)
		printf("%d\n",d[i]);
	return 0;
}