#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009,
		  MAXM = 209;
const int MOD = 998244353;

vector<int> g[MAXN];
int n, m;
int f[MAXN][MAXM][2];
int size[MAXN];
int tmp[MAXM][2];

void dfs(int u, int rt)
{
	int v;
	sort(g[u].begin(), g[u].end());
	if (rt)
		g[u].erase( lower_bound(g[u].begin(), g[u].end(), rt) );
	memset(f[u], 0, sizeof(f[u]));
	size[u] = 1;
	f[u][0][0] = 1;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		int v = g[u][i];
		dfs(v, u);
	}
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		memset(tmp, 0, sizeof(tmp));
		for (int j = 0; j < m && j < size[u]; j++)
			for (int k = 0; k < m && k < size[v]; k++)
			{
				(tmp[(j + k + 1) % m][1]+=1ll * f[u][j][0] * f[v][k][0] % MOD)%=MOD;
				(tmp[(j + k) % m][0]+= 1ll * f[u][j][0] * f[v][k][0] % MOD)%=MOD;
				(tmp[(j + k) % m][0]+= 2ll * f[u][j][0] * f[v][k][1] % MOD)%=MOD;
				(tmp[(j + k) % m][1]+= 2ll * f[u][j][1] * f[v][k][0] % MOD)%=MOD;
				(tmp[(j + k) % m][1]+= 2ll * f[u][j][1] * f[v][k][1] % MOD)%=MOD;
			}
		memcpy(f[u], tmp, sizeof(tmp));
		size[u] += size[v];
	}
	return ;
}

int main()
{
	freopen("2589.in","r",stdin);
	freopen("2589.out","w",stdout);
	int ttt,x,y;
	scanf("%d", &ttt);
	for (;ttt--;)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		dfs(1, 0);
		printf("%d\n", (f[1][0][0] + f[1][0][1]) % MOD);
	}
	return 0;
}