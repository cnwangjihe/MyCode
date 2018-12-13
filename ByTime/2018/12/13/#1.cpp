#include<bits/stdc++.h>
using namespace std;

const int N=25,M=N*N*N*N*2;
const int INF=0x3f3f3f3f;
const double eps=1e-10,DNF=(double)1e50;
int n,m,cnt,nod;
int mp[N][N];
double V[N],R[N],E[N],lim[N];

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return ret;
}

int tot,S,T,head[M],cur[M],dis[M];
queue<int>q;
struct Tway{int v,nex;double w;}e[M];
void add(int u,int v,double w)
{
	//printf("add:%d %d %lf\n",u,v,w);
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],0};head[v]=tot;
}
bool bfs()
{
	for(int i=0;i<=nod;++i) dis[i]=-1,cur[i]=head[i];
	while(!q.empty()) q.pop();
	q.push(S);dis[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			//printf("%d %d %d %d %lf\n",u,v,dis[u],dis[v],e[i].w);
			if(e[i].w>eps && !~dis[v]) dis[v]=dis[u]+1,q.push(v);
		}
	}
	for (int i=0;i<nod;i++)
		cerr << "~~~ : " << dis[i] << "\n";
	return ~dis[T];
}
double dfs(int x,double flow)
{
	if(x==T || flow<eps) return flow;
	double used=0,w;
	for(int &i=cur[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dis[v]==dis[x]+1 && (w=dfs(v,min(flow-used,e[i].w)))>eps)
		{
			e[i].w-=w;e[i^1].w+=w;used+=w;
			if(used+eps>=flow) break;
		}
	}
	return used;
}	
double dinic(){double res=0;while(bfs()) {res+=dfs(S,INF);cerr << res;}}

struct node
{
	double x,y;
	node(){}
	node(double x,double y):x(x),y(y){}
	void in(){x=read();y=read();}
	void out(){printf("%lf %lf\n",x,y);}
}a[N][2],b[N];
struct line
{
	node a,b;
	line(){}
	line(node a,node b):a(a),b(b){}
};
struct data
{
	int u,v,w;
	double pos;
	data(){}
	data(double pos,int u,int v,int w):pos(pos),u(u),v(v),w(w){}
	void out(){printf("%lf %d %d %d\n",pos,u,v,w);}
}s[M];
bool cmp(const data&a,const data &b){return a.pos<b.pos;}
node operator + (const node&a,const node&b){return node(a.x+b.x,a.y+b.y);}
node operator - (const node&a,const node&b){return node(a.x-b.x,a.y-b.y);}
node operator * (const node&a,double x){return node(a.x*x,a.y*x);}
node rotate(const node&a){return node(-a.y,a.x);}
double getlen(const node&a){return sqrt(a.x*a.x+a.y*a.y);}
double dot(const node&a,const node&b){return a.x*b.x+a.y*b.y;}
double css(const node&a,const node&b){return a.x*b.y-a.y*b.x;}
node linecross(const line&a,const line&b)
{
	node x=a.a-b.a;
	double t=css(b.b,x)/css(a.b,b.b);
	return a.a+a.b*t;
}
node cross(const line&l,const node&p,double v,double r)
{
	node mid=linecross(l,line(p,rotate(l.b)));
	double t=getlen(mid-p),len;
	if(t+eps>r) return node(DNF,-DNF);
	t=sqrt(r*r-t*t);len=getlen(mid-l.a);
	if(dot(mid-l.a,l.b)<0) len=-len;
	return node((len-t)/v,(len+t)/v);
}
void init()
{
	n=read();m=read();
	for(int i=1;i<=n;++i) b[i].in();
	for(int i=1;i<=m;++i)
	{
		a[i][0].in();a[i][1].in();
		V[i]=read();R[i]=read();E[i]=read();
		lim[i]=getlen(a[i][1]-a[i][0])/V[i];
	}
	for(int i=1;i<=m;++i)
	{
		line t=line(a[i][0],a[i][1]-a[i][0]);
		for(int j=1;j<=n;++j)
		{
			node t2=cross(t,b[j],V[i],R[i]);
			t2.x=max(t2.x,0.0);t2.y=min(t2.y,lim[i]);
			if(t2.x<t2.y+eps) s[++cnt]=data(t2.x,i,j,1),s[++cnt]=data(t2.y,i,j,-1);
		}
	}
	for(int i=1;i<=cnt;++i) s[i].out();
	sort(s+1,s+cnt+1,cmp);
}
void getmap()
{
	int cst=0;S=m+1;T=m+2;tot=1;nod=T;
	//printf("S:%d T:%d\n",S,T);
	for(int i=1;i<=m;++i) add(S,i,E[i]);
	for(int i=1;i<=cnt;++i)
	{
		cst+=s[i].w;mp[s[i].u][s[i].v]+=s[i].w;
		if(i^cnt && (s[i].pos+eps<s[i+1].pos))
		{
			if(!cst) continue;
			double t=s[i+1].pos-s[i].pos;
			for(int j=1;j<=n;++j)
			{
				bool fg=0;
				for(int k=1;k<=m;++k) if(mp[k][j])
				{
					if(!fg) add(++nod,T,t),fg=1;
					add(k,nod,INF);
				}
			}
		}
	}
}

int main()
{
	freopen("t1.out","w",stdout);
	init();getmap();dinic();
	return 0;
}