#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <iostream>
using namespace std;
#define R register
#define IN inline
#define W while
#define ll long long
#define MOD 1000000007
#define MX 3005000
int n, cnt, last, cur, ans;
char *str[MX], buf[MX], Out[MX];
int nex[MX][4], lb[MX], rb[MX];
bool exi[MX][4], vis[MX];
int to[MX][4], par[MX], siz[MX], len[MX], root[MX], l[MX];
IN char Get(R char c)
{
	switch (c)
	{
		case 'A': return '0'; break;
		case 'C': return '1'; break;
		case 'G': return '2'; break;
		case 'T': return '3'; break;
	}
}
IN char Give(R int id)
{
	switch (id)
	{
		case 0: return 'A'; break;
		case 1: return 'C'; break;
		case 2: return 'G'; break;
		case 3: return 'T'; break;
	}
}
namespace SAM
{
	IN void insert(R int num, R int id)
	{
		R int now, tar;
		cur = ++cnt; len[cur] = len[last] + 1;
		for (now = last; (~now) && (!to[now][id]); now = par[now]) to[now][id] = cur;
		if (now < 0) return last = cur, par[cur] = 0, void();
		tar = to[now][id];
		if (len[tar] == len[now] + 1) return last = cur, par[cur] = tar, void();
		int nw = ++cnt; len[nw] = len[now] + 1;
		std::memcpy(to[nw], to[tar], sizeof(to[nw]));
		par[nw] = par[tar], par[tar] = par[cur] = nw;
		for (; (~now) && to[now][id] == tar; now = par[now]) to[now][id] = nw;
		last = cur;
	}
	int DFS(R int now)
	{
		if (vis[now]) return siz[now];
		vis[now] = true; siz[now] = 1;
		for (R int i = 0; i < 4; ++i)
		if (to[now][i]) (siz[now] += DFS(to[now][i])) %= MOD;
		return siz[now];
	}
	void DFS(R int now, R int dgt)
	{
		puts(Out); ++ans;
		for (R int i = 0; i < 4; ++i)
		{
			if (!to[now][i]) continue;
			Out[dgt] = Give(i);
			DFS(to[now][i], dgt + 1);
		}
		Out[dgt - 1] = '\0';
	}
}
int main(void)
{
	int typ;
//	freopen("copy.in", "r", stdin);
//	freopen("copy.out", "w", stdout);
	scanf("%d", &n);
	for (R int i = 1; i <= n; ++i)
	{
		root[i] = ++cnt;
		par[root[i]] = -1;
		scanf("%s", buf + 1);
		l[i] = std::strlen(buf + 1);
		str[i] = new char[l[i] + 5];
		std::memcpy(str[i], buf, l[i] + 3);
		for (R int j = 1; j <= l[i]; ++j)
		{
			str[i][j] = Get(str[i][j]);
			exi[i][str[i][j] - '0'] = true;
			cerr << str[i][j];
		}
		cerr << str[i] << '\n';
	}
	for (R int i = n - 1; i; --i)
	{
		for (R int j = 0; j < 4; ++j)
		{
			if (exi[i + 1][j]) nex[i][j] = i + 1;
			else nex[i][j] = nex[i + 1][j];
			cerr << nex[i][j];
		}
	}
	root[1] = 0, par[0] = -1, par[1] = 0; cnt = 0;
	for (R int i = 1; i <= n; ++i)
	{
		lb[i] = cnt + 1; last = root[i];
		for (R int j = 1; j <= l[i]; ++j)
		SAM::insert(i, str[i][j] - '0');
		rb[i] = cnt;
	}
	for (R int i = 1; i <= n; ++i)
	{
		for (R int j = lb[i]; j <= rb[i]; ++j)
		{
			for (R int k = 0; k < 4; ++k)
			{
				if ((!to[j][k]) && nex[i][k])
					cerr << i << ' ' << j <<  ' ' << k << '\n',
				to[j][k] = to[root[nex[i][k]]][k];
			}
		}
	}
	scanf("%d", &typ);
	if (typ == 0) printf("%d", SAM::DFS(root[1]));
	else SAM::DFS(root[1], 0), printf("%d", ans);
}