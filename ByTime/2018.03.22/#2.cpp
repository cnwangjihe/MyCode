#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const double Maxn = 1e9;
const int N = 205, M = 8e4 + 5;
const double eps = 1e-8;
int pre[N], nxt[M], to[M], lst[N], fr[M], flw[M], Q[M];
int n, s, t, T; bool vis[N];
double a[N][N], b[N][N], cst[M], Ans, dis[N]; 
template <class T> inline void CkMin(T &a, const T b) {if (a > b) a = b;}
inline void Add(const int x, const int y, const int z, const double g)
{
	nxt[++T] = lst[x]; lst[x] = T; to[T] = y; fr[T] = x; flw[T] = z; cst[T] = g;
	nxt[++T] = lst[y]; lst[y] = T; to[T] = x; fr[T] = y; flw[T] = 0; cst[T] = -g;
}
inline bool Bul()
{
	for (int i = s; i <= t; ++i) dis[i] = -Maxn;
	int te = 0, we = 1, x, y; 
	dis[Q[1] = s] = 0.0;
	while (te < we)
	{
		x = Q[++te]; vis[x] = false;
		for (int i = lst[x]; i; i = nxt[i])
		if (dis[y = to[i]] < dis[x] + cst[i] && flw[i])
		{
			dis[y] = dis[x] + cst[i]; pre[y] = i; 
			if (!vis[y]) vis[y] = true, Q[++we] = y;
		}
	}
	cerr << dis[t] << endl;
	return dis[t] > -Maxn;
}
inline void Deal()
{
	int Mif = Maxn;
	for (int i = pre[t]; i; i = pre[fr[i]]) CkMin(Mif, flw[i]);
	for (int i = pre[t]; i; i = pre[fr[i]])
	 flw[i] -= Mif, flw[i ^ 1] += Mif, Ans += (double)Mif * cst[i];
}
inline bool check(const double mi)
{
	T = 1; memset(lst, 0, sizeof(lst));
	for (int i = 1; i <= n; ++i) 
	 Add(s, i, 1, 0), Add(i + n, t, 1, 0);
	for (int i = 1; i <= n; ++i)
	 for (int j = 1; j <= n; ++j)
	  Add(i, j + n, 1, a[i][j] - mi * b[i][j]);
	Ans = 0.0; while (Bul()) Deal();
	cerr << Ans << endl;
	return (Ans <= 0); 
}
int main()
{
	scanf("%d", &n); s = 0; t = (n << 1) + 1;
	for (int i = 1; i <= n; ++i)
	 for (int j = 1; j <= n; ++j) scanf("%lf", &a[i][j]);
	for (int i = 1; i <= n; ++i)
	 for (int j = 1; j <= n; ++j) scanf("%lf", &b[i][j]);
	double l = 0, r = 1e4;
	check(100);
//	while (r - l >= eps)
//	{
//		double mid = (l + r) / 2;
//		(check(mid) ? r : l) = mid;
//	} 
	return printf("%.6lf\n", l), 0;
}