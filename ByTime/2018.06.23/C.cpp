#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, x, y, cnt, last;
long long z, Max1, Max2, ans1, ans2, t, lastsum;
int tot, point[MAXN], nxt[MAXN * 2], v[MAXN * 2];
long long c[MAXN * 2];
int father[MAXN], o[MAXN];
long long len[MAXN], length[MAXN], f[MAXN], g[MAXN], s[MAXN], sum[MAXN], delta[MAXN * 4];
bool vis[MAXN], flag;

struct hp
{
	long long val;
	int num;
} maxn[MAXN * 4], _maxn[MAXN * 4], minn[MAXN * 4], _minn[MAXN * 4], a[5];

inline int read()
{
	char ch = getchar();
	int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

void _connect(int x, int y, long long z)
{
	++tot;
	nxt[tot] = point[x];
	point[x] = tot;
	v[tot] = y;
	c[tot] = z;
	++tot;
	nxt[tot] = point[y];
	point[y] = tot;
	v[tot] = x;
	c[tot] = z;
	return ;
}

inline void Circle(int x, int pt)
{
	while (x != pt)
	{
		o[++cnt] = x;
		x = father[x];
	}
	o[++cnt] = pt;
}
inline void dfs(int x, int fa)
{
	vis[x] = 1;
	father[x] = fa;
	for (int i = point[x]; i && (!flag); i = nxt[i])
		if (v[i] != fa)
		{
			len[v[i]] = c[i];
			if (vis[v[i]])
			{
				Circle(x, v[i]);
			//	cerr << x << "IOSDIOAIPDS\n";
				flag = 1;
				break;
			}
			dfs(v[i], x);
		}
}
void treedp(int x, int fa)
{
	for (int i = point[x]; i; i = nxt[i])
		if (v[i] != fa && !vis[v[i]])
		{
			treedp(v[i], x);
			if (f[v[i]] + c[i] > f[x])
			{
				g[x] = f[x];
				f[x] = f[v[i]] + c[i];
			}
			else g[x] = max(g[x], f[v[i]] + c[i]);
		}
	Max1 = max(Max1, f[x] + g[x]);
	Max2 = max(Max2, f[x]);
	return ;
}
inline int cmpmax(hp a, hp b)
{
	return a.val > b.val;
}
inline int cmpmin(hp a, hp b)
{
	return a.val < b.val;
}
inline void _down(int u, int l, int r, int mid)
{
	if (!delta[u])
		return ;
	maxn[u << 1].val += delta[u];
	_maxn[u << 1].val += delta[u];
	minn[u << 1].val += delta[u];
	_minn[u << 1].val += delta[u];
	maxn[u << 1 | 1].val += delta[u];
	_maxn[u << 1 | 1].val += delta[u];
	minn[u << 1 | 1].val += delta[u];
	_minn[u << 1 | 1].val += delta[u];
	delta[u << 1] += delta[u];
	delta[u << 1 | 1] += delta[u];
	delta[u] = 0;
	return ;
}
inline void _up(int u)
{
	a[1].val = maxn[u << 1].val, a[1].num = maxn[u << 1].num;
	a[2].val = maxn[u << 1 | 1].val, a[2].num = maxn[u << 1 | 1].num;
	a[3].val = _maxn[u << 1].val, a[3].num = _maxn[u << 1].num;
	a[4].val = _maxn[u << 1 | 1].val, a[4].num = _maxn[u << 1 | 1].num;
	sort(a + 1, a + 5, cmpmax);

	maxn[u].val = a[1].val, maxn[u].num = a[1].num;
	for (int i = 2; i <= 4; i++)
		if (a[i].num != maxn[u].num)
		{
			_maxn[u].val = a[i].val, _maxn[u].num = a[i].num;
			break;
		}

	a[1].val = minn[u << 1].val, a[1].num = minn[u << 1].num;
	a[2].val = minn[u << 1 | 1].val, a[2].num = minn[u << 1 | 1].num;
	a[3].val = _minn[u << 1].val, a[3].num = _minn[u << 1].num;
	a[4].val = _minn[u << 1 | 1].val, a[4].num = _minn[u << 1 | 1].num;
	sort(a + 1, a + 5, cmpmin);

	minn[u].val = a[1].val, minn[u].num = a[1].num;
	for (int i = 2; i <= 4; i++)
		if (a[i].num != minn[u].num)
		{
			_minn[u].val = a[i].val, _minn[u].num = a[i].num;
			break;
		}
	return ;
}
void build(int u, int l, int r)
{
//	cerr << u << ' ' << l << ' ' << r << ' ';
	if (l == r)
	{
		maxn[u].val = _maxn[u].val = sum[l] + s[l];
		minn[u].val = _minn[u].val = sum[l] - s[l];
		maxn[u].num = _maxn[u].num = minn[u].num = _minn[u].num = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	_up(u);
	return ;
}
void interval_change(int u, int l, int r, int lrange, int rrange, long long v)
{
	if (lrange <= l && r <= rrange)
	{
		maxn[u].val += v;
		_maxn[u].val += v;
		minn[u].val += v;
		_minn[u].val += v;
		delta[u] += v;
		return;
	}
	int mid = (l + r) >> 1;
	_down(u, l, r, mid);
	if (lrange <= mid) interval_change(u << 1, l, mid, lrange, rrange, v);
	if (mid + 1 <= rrange) interval_change(u << 1 | 1, mid + 1, r, lrange, rrange, v);
	_up(u);
	return ;
}
inline long long query()
{
	if (maxn[1].num != minn[1].num) return maxn[1].val - minn[1].val;
	else return max(maxn[1].val - _minn[1].val, _maxn[1].val - minn[1].val);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		x = read(),	y = read(), z = read();
		_connect(x, y, (long long)z);
	}
	dfs(1, 0);
	for (int i = 1; i <= cnt; i++)
		length[i] = len[o[i]];
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= cnt; i++)
		vis[o[i]] = 1;
	for (int i = 1; i <= cnt; i++)
	{
		Max1 = Max2 = 0;
		treedp(o[i], 0);
		ans1 = max(ans1, Max1);
		s[i] = Max2;
	}
	for (int i = 1; i < cnt; i++)
		sum[i + 1] = sum[i] + length[i];

	build(1, 1, cnt);
//	cerr << "Black!\n";
	t = query();
	ans2 = t;
	lastsum = sum[cnt];
	last = cnt;
	for (int i = 1; i < cnt; i++)
	{
		interval_change(1, 1, cnt, 1, cnt, -length[i]);
		interval_change(1, 1, cnt, i, i, lastsum + length[last]);
		t = query();
		ans2 = min(ans2, t);
		lastsum = lastsum - length[i] + length[last];
		last = i;
	}
	printf("%0.1f\n", (double)max(ans1, ans2) / 2.0);
	return 0;
}