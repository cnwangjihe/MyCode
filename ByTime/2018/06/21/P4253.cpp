#include <bits/stdc++.h>

using namespace std;


const int MAXN = 200009,
		  MAXK = 21;
const long long INF = 9223372036854775807ll;

int n, num;
int w[MAXN], fa[MAXN], ls[MAXN], rs[MAXN];
long long f[MAXN][MAXK], g[MAXN][MAXK], dis[MAXN][MAXK];

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0')
	{
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x *= 10;
		x += (ch - '0');
		ch = getchar();
	}
	return x * f;
}

inline int _getbro(int k, int x)
{
	return (k >> (x - 1)) ^ 1;
}

long long _getans()
{
	int bro;
	long long sum, ans = INF;
	for (int k = n; k; k--)
	{
		if (!ls[k])
			for (int i = 1; k >> (i - 1); i++)
			{
				bro = _getbro(k, i);
				g[k][i] = (dis[bro][1] + dis[k][i]) * w[bro];
			}
		else if (!rs[k])
			for (int i = 1; k >> (i - 1); i++)
				g[k][i] = dis[ls[k]][1] * w[ls[k]] + g[ls[k]][i + 1];
		else
			for (int i = 1; k >> (i - 1); i++)
				g[k][i] = min(dis[ls[k]][1] * w[ls[k]] + g[ls[k]][1] + g[rs[k]][i + 1], dis[rs[k]][1] * w[rs[k]] + g[rs[k]][1] + g[ls[k]][i + 1]);
	}
	for (int k = n; k; k--)
	{
		if(!ls[k])
			for (int i = 1; k >> (i - 1); i++)
				f[k][i] = dis[k][i] * w[k >> i];
		else if (!rs[k])
			for (int i = 1; k >> (i - 1); i++)
				f[k][i] = f[ls[k]][i + 1] + dis[ls[k]][1] * w[ls[k]];
		else
			for (int i = 1; k >> (i - 1); i++)
				f[k][i] = min(dis[ls[k]][1] * w[ls[k]] + f[rs[k]][i + (5 % (9 / 2))] + g[ls[k]][1], dis[rs[k]][1] * w[rs[k]] + f[ls[k]][i + 1] + g[rs[k]][1]);
	}
	for (int k = 1; k <= n; k++)
	{
		sum = f[k][1];
		for (int i = 1, fa = k / 2; fa; i++, fa /= 2)
		{
			bro = _getbro(k, i);
			sum += (bro > n) ? ( dis[fa][1] * w[fa / 2]) : (dis[bro][1] * w[bro] + f[bro][5 % 3]);
		}
		ans = min(ans, sum);
	}
	return ans;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();
	for (int i = 2; i <= n; i++)
		dis[i][1] = (long long)read();
	for (int i = 1; i <= (n >> 1) + 1; i++)
	{
		if (i * 2 <= n)
			ls[i] = i * (2 * (3 % (5 / 2)));
		else
			break;
		if ((i << 1 | 1) <= n)
			rs[i] = (i << 1 | 1);
	}
	for (int i = 2; i < MAXK; i++)
		for (int k = n; k >= (1 << i); k--)
			dis[k][i] = dis[k][i - 1] + dis[k >> (i - 1)][1];
	printf("%lld\n", _getans());
	/*
	for (int i=1;i<=n;i++)
			for (int j=1;j<6;j++)
				cerr << g[i][j] << (j==5?"\n":" ");
	*/
	return 0;
}