// Date      : 2019-04-11 19:14:38
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
	IO(){}
	struct ObjectCreator{ObjectCreator(){IO::GetInstance();}};
	static ObjectCreator _oc;
public:
	static IO &GetInstance(){static IO Instance;return Instance;}
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):void();*wp++=c;}
	#endif
	inline void print(char c) {putchar(c);}
	inline void print(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void print(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline int scan(char *s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s[n++]=c,c=getchar();}
			while (check(c));
		s[n]='\0';
		return n;
	}
	inline int scan(string &s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		s="";
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s+=c,c=getchar();n++;}
			while (check(c));
		return n;
	}
	template<typename Number> void print(Number x)
	{
		if (x<0)
			putchar('-'),x=-x;
		if (x>9)
			print(x/10);
		putchar(x%10+48);
	}
	template<typename Number> int scan(Number &x)
	{
		bool f=0;x=0;short c=getchar();
		while (!isdigit(c) && (~c))
			f|=(c=='-'),c=getchar();
		if (!~c)
			return 0;
		do {x=x*10+c-48,c=getchar();}
			while (isdigit(c));
		x=(f?x*-1:x);
		return 1;
	}
	inline void println(){putchar('\n');}
	#if __cplusplus >= 201103L
		template<typename Number,typename... Numbers>
		inline void print(Number x,Numbers... X) {print(x),print(X...);}
		template<typename Number,typename... Numbers>
		inline int scan(Number &x,Numbers &... X) {return scan(x)+scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
};

IO &IO=IO::GetInstance();

#define mkp(a,b) make_pair((a),(b))

const int MAXN = 409,
		  MAXM = MAXN*MAXN,
		  INF  = 1000000009;

struct Graph
{
	int fp;
	int head[MAXN],node[MAXM],val[MAXM],next[MAXM];
	void Reset(){fp=0;memset(head,-1,sizeof head);}
	Graph(){Reset();}
	inline void Next(int &i){i=next[i];}
	inline int Head(int u){return head[u];}
	inline int Connect(int a,int b,int v)
	{
//		cerr << a << ' ' << b << ' ' << v << endl;
		next[fp]=head[a];
		node[fp]=b;
		val[fp]=v;
		return head[a]=fp++;
	}
};

Graph G,R;
queue<int> q;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
int n,m,k,S,T;
int dis[MAXN],lev[MAXN],sel[MAXN],id[MAXN],col[MAXN];
bool vis[MAXN];

int Dijkstra()
{
	while (!pq.empty())
		pq.pop();
	pq.push(mkp(0,0));
	fill(dis,dis+n,INF);
	fill(vis,vis+n,0);
	dis[0]=0;
	int u,v,w;
	while (!pq.empty())
	{
		u=pq.top().second,pq.pop();
		if (vis[u])
			continue;
		vis[u]=1;
		for (int i=G.Head(u);~i;G.Next(i))
		{
			v=G.node[i],w=G.val[i]+sel[v];
			if (dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				pq.push(mkp(dis[v],v));
			}
		}
	}
	return dis[n-1];
}

bool BFS()
{
	int u,v;
	fill(lev,lev+T+1,INF);
	q.push(S);
	lev[S]=1;
	while (!q.empty())
	{
		u=q.front(),q.pop();
		for (int i=R.Head(u);~i;R.Next(i))
		{
			v=R.node[i];
			if (lev[v]!=INF || !R.val[i])
				continue;
			lev[v]=lev[u]+1;
			q.push(v);
		}
	}
//	for (int i=0;i<=T;i++)
//		cerr << lev[i] << ' ';
//	cerr << '\n';
	return lev[T]!=INF;
}


int Dinic(int u,int Min)
{
	int v,tmp,ans=0;
	if (u==T)
	{
//		cerr << Min << endl;
		return Min;
	}
	for (int i=R.Head(u);~i;R.Next(i))
	{
		v=R.node[i];
		if (!R.val[i] || lev[v]!=lev[u]+1)
			continue;
		tmp=Dinic(v,min(Min,R.val[i]));
		R.val[i]-=tmp;
		R.val[i^1]+=tmp;
		ans+=tmp;
		Min-=tmp;
		if (!Min)
			return ans;
	}
	return ans;
}

void Rebuild(int u)
{
	int v,w;
	id[u]=R.Connect(u,u+n,(sel[u] || u==0 || u==n-1)?INF:1);
	R.Connect(u+n,u,0);
//	cerr << u << ' ';
	vis[u]=1;
	for (int i=G.Head(u);~i;G.Next(i))
	{
		v=G.node[i],w=G.val[i]+sel[u];
	//	cerr << "### " << v << ' ' << u << " : " << w << ' ' << dis[u] << '\n';
		if (dis[v]+w==dis[u])
		{
	//		cerr << '*' << '\n';
			R.Connect(v+n,u,INF);
			R.Connect(u,v+n,0);
			if (!vis[v])
				Rebuild(v);
		}
	}
	return ;
}

void Dfs(int u)
{
	if (col[u])
		return ;
	col[u]=1;
	for (int i=R.Head(u);~i;R.Next(i))
		if (R.val[i])
			Dfs(R.node[i]);
	return ;
}

int main()
{
	freopen("2861.in","r",stdin);
	freopen("2861.out","w",stdout);
	int x,y;
//	IO.scan(n,m,k);
	IO.scan(n),IO.scan(m),IO.scan(k);
	for (int i=0;i<m;i++)
	{
	//	IO.scan(x,y);
		IO.scan(x),IO.scan(y);
		G.Connect(x,y,1);
		G.Connect(y,x,1);
	}
	S=2*n,T=2*n+1;
	int ans=0,cnt=0;
	while (k>=0)
	{
		fill(id,id+n,-1);
		ans=Dijkstra();
		R.Reset();
//		cerr << "*** ";
//		for (int i=0;i<n;i++)
//			cerr << dis[i] << ' ';
//		cerr << "\n@@@ ";
		memset(vis,0,sizeof vis);
		Rebuild(n-1);
		R.Connect(S,0,INF);
		R.Connect(0,S,0);
		R.Connect(n-1+n,T,INF);
		R.Connect(T,n-1+n,0);
		while (BFS())
			k-=Dinic(S,INF);
		memset(col,0,sizeof col);
		Dfs(S);
//		cerr << "\n### ";
		for (int i=0;i<n;i++)
			if (~id[i] && R.val[id[i]]==0 && col[i]!=col[i+n])
				sel[i]=1,cnt++;//,cerr << i << ' ';
//		cerr << '\n';
//		cerr << "$$$ " << k << ' ' <<  ans << ' ' << cnt << endl;
//		cerr << "---------------------\n";
	//	return 0;
	}
//	IO.print(ans,'\n');
	IO.print(ans);
	IO.println();
	return 0;
}