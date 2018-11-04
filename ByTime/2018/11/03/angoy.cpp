#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

const int N = 3010;

struct po { int val, w; } t[N];

int f[N][N];

bool _sort(po x, po y) {
	return x.w > y.w;
}

signed main() {

	freopen("angoy.in", "r", stdin);
	freopen("angoy.out", "w", stdout);

	int n; scanf("%lld", &n);
	for (int i=1; i<=n; i++)
		scanf("%lld%lld", &t[i].val, &t[i].w);

	sort(t+1, t+n+1, _sort);
	
	f[0][0] = 0;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=i; j++) {
			f[i][j] = max(f[i-1][j], max(f[i][j], f[i-1][j-1] + t[i].val - (j-1) * t[i].w));
		}
	}
	
	int ans = 0;
	for (int i=1; i<=n; i++) ans = max(ans, f[n][i]);

	printf("%lld\n", ans);

	return 0;
}
