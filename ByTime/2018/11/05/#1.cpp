#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int N = 100010;

struct edge { int nx, to, len; } e[N];

int he[N], tot = 0;
void AddEdge (int u, int v, int l) {
	e[++tot] = edge{he[u], v, l}, he[u] = tot;	
}

int n, m;
int dist[N], cnt[N];
bool f[N];
stack <int> S;

bool spfa() {
	for (int i=1; i<=n; i++) {
		S.push(i), cnt[i] = 1, f[i] = true, dist[i] = 0;
	}
	
	while (!S.empty()) {
		
		int u = S.top(); S.pop(), f[u] = false;
		
		for (int h=he[u]; h!=-1; h=e[h].nx) {
			
			int v = e[h].to, l = e[h].len;
			if (dist[v] > dist[u] + l) {
				dist[v] = dist[u] + l;	
				if(++cnt[v] > n) return false;
				if(f[v] == false) S.push(v);
			}	
		}
	}
	return true;
}

int main() {
    
	freopen ("farm.in", "r", stdin);
    freopen ("farm.out", "w", stdout);
    
	scanf("%d%d", &n, &m);
	memset(he, -1, sizeof(he));
	
	while (m --) {
		int x, a, b, c; scanf("%d", &x);
		if (x == 1) {
			scanf("%d%d%d", &a, &b, &c); 
			AddEdge(a, b, - c);
		}
		else if (x == 2) {
			scanf("%d%d%d", &a, &b, &c);
			AddEdge(b, a, c);
		}
		else {
			scanf("%d%d", &a, &b);
			AddEdge(a, b, 0), AddEdge(b, a, 0);
		}
	}
	printf(spfa() ? "Yes\n" : "No\n");
	return 0; 
}
