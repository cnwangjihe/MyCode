#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>

using namespace std;

const int N = 100010;
const int oo = 2100000000;

int n, l, ans = 0, a[N];
void dfs(int x, int sum) {
	if(x>=n-l && x<n) {
		ans += sum; return ;
	}
	int t;
	for (int i=x+l; i>=x+1; i--) {
		if(a[i]) {
			t = min(a[i], sum);
			sum -= t, a[i] -= t, dfs(i, t);
		}
		if(sum == 0) return ;
	}
}

int main() {

///	freopen("2697.in", "r", stdin);
//	freopen("2697.out", "w", stdout);

	scanf("%d%d", &n, &l);
	
	for (int i=1; i<n; i++) scanf("%d", &a[i]);

	dfs(0, oo);
	
	printf("%d\n", ans);

	return 0;
}
