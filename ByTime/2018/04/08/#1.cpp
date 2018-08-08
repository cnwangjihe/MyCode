#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define N 500

int n,S,T;
bool in[N][N];
bool check[N*N];

inline int read() {
	int tmp=0,w=1;
	char ch=0;
	while(!isdigit(ch)) {if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)) tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}

struct node {
	int u,v,c,f,nex;
}e[N*N],ee[N*N];
int tot=1,h[N],use[N];
void add(int u,int v,int c,int f) {
	e[++tot].u=u,e[tot].v=v,e[tot].c=c,e[tot].f= f,e[tot].nex=h[u],h[u]=tot;
	e[++tot].u=v,e[tot].v=u,e[tot].c=0,e[tot].f=-f,e[tot].nex=h[v],h[v]=tot;
}

int dis[N];
bool vis[N];
bool donot[N*N];
deque<int>q;
bool spfa() {
	for(int i=S;i<=T;++i) dis[i]=-1e9,vis[i]=0;
	q.push_back(T);
	dis[T]=0;
	int x,xx;
	while(!q.empty()) {
		x=q.front();
		q.pop_front();
		vis[x]=0;
		for(int i=h[x];i;i=e[i].nex) {
			xx=e[i].v;
			if(donot[i]) continue;
			if(e[i^1].c&&dis[xx]<dis[x]-e[i].f) {
				dis[xx]=dis[x]-e[i].f;
				if(!vis[xx]) {
					vis[xx]=1;
					if(q.empty()||dis[xx]<dis[q.front()]) q.push_back(xx);
					else q.push_front(xx);
				}
			}
		}
	}
	return dis[S]>-1e9;
}
bool mark[N];
int dfs(int x,int want) {
	mark[x]=1;
	if(x==T||!want) return want;
	int f=0,get=0,xx=0;
	for(int i=use[x];i;i=e[i].nex) {
		if(donot[i]) continue;
		xx=e[i].v;
		if(e[i].c&&!mark[xx]&&dis[xx]==dis[x]-e[i].f) {
			f=dfs(xx,min(want,e[i].c));
			if(!f) continue;
			e[i].c-=f;
			e[i^1].c+=f;
			get+=f;
			want-=f;
			use[x]=i;
			if(!want) break;
		}
	}
	return get;
}

int mfmc() {
	int res=0;
	while(spfa()) {
		mark[T]=1;
		while(mark[T]) {
			for(int i=S;i<=T;++i) use[i]=h[i],mark[i]=0;
			res+=dis[S]*dfs(S,1e9);
		}
	}
	return res;
}

int main()
{
	freopen("P3967.in","r",stdin);
	freopen("#1.out","w",stdout);
	scanf("%d",&n);
	S=0,T=n+n+1;
	int x;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			x=read();
			add(i,j+n,1,x);
		} 
	}
	int cut=tot;
	for(int i=1;i<=n;++i) add(S,i,1,0),add(i+n,T,1,0);
	memcpy(ee,e,sizeof(e));
	int ans=mfmc();
	for(int i=2;i<=cut;i+=2) if(!e[i].c) check[i]=1;
	printf("%d\n",ans);
	for(int i=2;i<=cut;i+=2) {
		if(check[i]) {
			donot[i]=1,donot[i^1]=1;
			memcpy(e,ee,sizeof(ee));    
			x=mfmc();
			if(x<ans) in[e[i].u][e[i].v]=1;
			donot[i]=0,donot[i^1]=0;
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			if(in[i][j+n]) printf("%d %d\n",i,j);
		}
	}
	return 0;
}