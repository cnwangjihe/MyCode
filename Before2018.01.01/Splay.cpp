#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 200000 + 10;

struct SplayTree
{
	int n, root;
	int Val[maxn];
	int Add[maxn], Min[maxn], Rev[maxn];
	int fa[maxn], c[maxn][2], size[maxn];

	void init()
	{
		n = root = 0;
		memset(c, 0, sizeof(c));
		memset(fa, 0, sizeof(fa));
	}
	void Push_up(int u)
	{ 
		Min[u] = Val[u];
		size[u] = size[c[u][0]] + size[c[u][1]] + 1;
		if(c[u][0]) Min[u] = min(Min[u], Min[c[u][0]]);
		if(c[u][1]) Min[u] = min(Min[u], Min[c[u][1]]);
	}
	void Push(int u)
	{
		if(fa[u]) Push(fa[u]);
		Push_down(u);
	}
	void Push_down(int u)
	{
		if(Add[u])
		{
			if(c[u][0]) Add[c[u][0]] += Add[u], Val[c[u][0]] += Add[u], Min[c[u][0]] += Add[u];
			if(c[u][1]) Add[c[u][1]] += Add[u], Val[c[u][1]] += Add[u], Min[c[u][1]] += Add[u];
		}
		if(Rev[u])
		{
			if(c[u][0]) Rev[c[u][0]] ^= 1;
			if(c[u][1]) Rev[c[u][1]] ^= 1;
			swap(c[u][0], c[u][1]);
		}
		Add[u] = Rev[u] = 0;
		return ;
	}
	int Newnode(int key) 
	{
		size[++n] = 1;
		Add[n] = Rev[n] = 0;
		Val[n] = Min[n] = key;
		return n;
	}
	void rotate(int u)
	{
		int v = fa[u], w = fa[v], t = c[v][1] == u;
		fa[c[u][t^1]] = v, c[v][t] = c[u][t^1];
		c[u][t^1] = v, fa[u] = w, fa[v] = u;

		if(root == v) root = u;
			else c[w][c[w][1] == v] = u;
		Push_up(v);
	}
	void Splay(int u, int p)
	{
		Push(u);
		while(fa[u] != p)
		{
			int v = fa[u], w = fa[v];
			if(fa[v] == p) 
				rotate(u);
			else if((c[v][0] == u) == (c[w][0] == v)) 
				rotate(v), rotate(u);
			else 
				rotate(u), rotate(u);
		}Push_up(u);
	}
	void insert(int key)
	{
		c[root][1] = Newnode(key);
		fa[c[root][1]] = root;
		Splay(c[root][1],0);
	}
	int find(int u, int k) {
		Push_down(u);
		int t = size[c[u][0]] + 1;
		if(t == k) 
			return u;
		else {
			if(t > k) return find(c[u][0], k);
			else return find(c[u][1], k-t);
		}
	}
	void update(int u, int v, int w) {
		int x = find(root, u), y = find(root, v+2);
		Splay(x, 0), Splay(y, root);
		Add[c[y][0]] += w;
		Val[c[y][0]] += w;
		Min[c[y][0]] += w;
	}
	void Reverse(int u, int v) {
		int x = find(root, u), y = find(root, v+2);
		Splay(x, 0), Splay(y, root);
		Rev[c[y][0]] ^= 1;
	}
	void Revolve(int u, int v, int w) {
		int m = v - u + 1; 
		w %= m; w = (w + m) % m;

		int x = find(root, u), y = find(root, u+1);
		int _x = find(root, v-w+1), _y = find(root, v+2);

		Splay(_x, 0), Splay(_y, root);
		int p = c[_y][0]; c[_y][0] = 0;

		Splay(x, 0), Splay(y, root);
		c[y][0] = p; fa[p] = y;
	}
	void Join(int u, int v) {
		int x = find(root, u+1), y = find(root, u+2);
		Splay(x, 0), Splay(y, root);
		c[y][0] = Newnode(v); fa[n] = y;
	}
	void del(int u) {
		int x = find(root, u), y = find(root, u+2);
		Splay(x, 0), Splay(y, root);
		c[y][0] = 0;
	}
	int query(int u, int v) {
		int x = find(root, u), y = find(root, v+2);
		Splay(x, 0), Splay(y, root);
		return Min[c[y][0]];
	}
}Spt;

char s[20];
int n, q, u, v, w;

int main()
{
	while(scanf("%d", &n) == 1 && n)
	{

		Spt.init();
		Spt.root = Spt.Newnode(INF);
		for(int i=1; i<=n; i++) {
			scanf("%d", &u);
			Spt.insert(u);
		}Spt.insert(INF);

		scanf("%d", &q);
		while(q--) {
			scanf("%s", s);
			if(s[0] == 'A') {
				scanf("%d%d%d", &u, &v, &w); if(u > v) swap(u, v);
				Spt.update(u, v, w);
			}else if(s[0] == 'R' && s[3] == 'E') {
				scanf("%d%d", &u, &v); if(u > v) swap(u, v);
				Spt.Reverse(u, v);
			}else if(s[0] == 'R' && s[3] == 'O') {
				scanf("%d%d%d", &u, &v, &w); if(u > v) swap(u, v);
				Spt.Revolve(u, v, w); 
			}else if(s[0] == 'I') {
				scanf("%d%d", &u, &v); 
				Spt.Join(u, v);
			}else if(s[0] == 'D') { 
				scanf("%d", &u);
				Spt.del(u);
			}else if(s[0] == 'M') {
				scanf("%d%d", &u, &v); if(u > v) swap(u, v);
				printf("%d\n", Spt.query(u, v));
			}
		}
	}
	return 0;
}
