#include <bits/stdc++.h>

using namespace std;

const int N=100010;
const int oo=1e9;

int n, m, K, t, dis[N];
bool v[N], p[N];
queue <int> q;
void bfs(int s) {
	
	int i, u, cnt=0;
	
	for (i=1; i<=n; i++) dis[i]=oo;
	dis[s]=0, q.push(s), v[s]=1, cnt++;
	
	while(!q.empty()) {
		u=q.front(); q.pop();
		for (i=t; i<=K; i+=2) {
			if(u-i<=0) break;
			if(!v[u-i]&&!p[u-i]) {
				if(u-i-((K-(i+1))/2)>0&&u+((K-(i+1))/2)<=n)
					dis[u-i]=dis[u]+1, q.push(u-i), v[u-i]=1, cnt++;	
			}
		}
		for (i=t; i<=K; i+=2) {
			if(u+i>n) break;
			if(!v[u+i]&&!p[u+i]) {
				if(u-((K-(i+1))/2)>0&&u+i+((K-(i+1))/2)<=n)	
					dis[u+i]=dis[u]+1, q.push(u+i), v[u+i]=1, cnt++;
			}
		}
	//	if(cnt==n-m) break;
	}
	return ;
}

int main() {
	t=clock();
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	
	int i, x;
	int S;
	
	scanf("%d%d%d%d", &n, &K, &m, &S);
	for (i=1; i<=m; i++) scanf("%d", &x), p[x]=true;
	
	if(K&1) t=2;
	else t=1;
	
	bfs(S);
	for (i=1; i<=n; i++) {
		if(dis[i]==oo) printf("-1 ");
		else printf("%d ", dis[i]);	
	}
	cerr << clock()-t;
	return 0;
}
