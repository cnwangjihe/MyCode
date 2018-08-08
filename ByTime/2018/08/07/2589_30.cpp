#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;

int _head[MAXN],_node[MAXN*2],_next[MAXN*2];
int u[MAXN],v[MAXN];
int d[MAXN],line[MAXN*10];
bool f[MAXN],_in[MAXN];
int ans,fp,n,m,mod;
int head,tail,c;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int main()
{
	freopen("2589.in","r",stdin);
	freopen("2589.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&mod);
		if (n>16)
			return 0;
		m=n-1;
		ans=0;
		for (int i=0;i<m;i++)
			scanf("%d%d",&u[i],&v[i]);
		for (int i=0;i<(1<<m);i++)
		{
			memset(_head,-1,sizeof _head);
			memset(f,0,sizeof f);
			memset(_in,0,sizeof _in);
			memset(d,0,sizeof d);
			head=tail=fp=c=0;
			for (int j=0;j<m;j++)
				if (i&(1<<j))
				{
					d[u[j]]++,d[v[j]]++;
					_connect(u[j],v[j]);
					_connect(v[j],u[j]);
				}
			for (int j=1;j<=n;j++)
				if (d[j]==1)
					line[tail++]=j;
			while (head!=tail)
			{
				int u=line[head++],v;
				if (d[u]==0)
					continue;
			//	if (i==5)
			//		cerr << u << endl;
				for (int k=_head[u];~k;k=_next[k])
				{
					v=_node[k];
					if (!f[v] && !f[u])
						c++,f[v]=1,f[u]=1;
					d[u]--,d[v]--;
					if (d[v]==1 && !_in[v])
						line[tail++]=v,_in[v]=1;
				}
			}
			if (c%mod==0)
			{
				ans++;
		//	cerr << i << ' ' << c << endl;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}