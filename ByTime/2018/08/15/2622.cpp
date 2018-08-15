#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2009,
		  MAXM = MAXN*MAXN;

int comp[MAXN];
int _head[MAXN],_node[MAXM],_next[MAXM];
int n,m,cnt,fp;
bool flag;
int mp[MAXN][MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u)
{
	comp[u]=cnt;
	for (int i=_head[u];~i;i=_next[i])
		if (comp[_node[i]]==-1)
			dfs(_node[i]);
	return ;
}

int main()
{
	freopen("2622.in","r",stdin);
	freopen("2622.out","w",stdout);
	int ttt,x,y;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		fp=cnt=0;
		flag=1;
		memset(comp,-1,sizeof comp);
		memset(_head,-1,sizeof _head);
		scanf("%d%d",&n,&m);
		memset(mp,0,sizeof mp);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			mp[x][y]=mp[y][x]=1;
		}
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (!mp[i][j])
				{
					_connect(i,n+j);
					_connect(n+j,i);
					_connect(i+n,j);
					_connect(j,i+n);
				}
		for (int i=1;i<=n*2;i++)
		{
			if (comp[i]==-1)
				cnt++,dfs(i);
		}
		for (int i=1;i<=n;i++)
			if (comp[i]==comp[n+i])
			{
				flag=0;
				break;
			}
	//	cerr << cnt << endl;
		printf("%s\n",flag?"YES":"NO");
	}
	return 0;
}