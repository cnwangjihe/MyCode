#include <bits/stdc++.h>
using namespace std;

const int mxn=4e5+10;
const int mxm=2e6+10;

int n,m;
int hd[mxn],node[mxm*2],nt[mxm*2],fp=0;

inline int read();
void con(int x,int y);
int u_f(int x);

int low[mxn],dfn[mxn],col[mxn],tim=0;
int st[mxn],top=0;
bool in[mxn];
int c=0;

void tarjan(int u,int e)
{
	if(!u) return ;
	
//	cerr<<u<<": "<<e<<endl;
	
	low[u]=dfn[u]=++tim;
	st[top++]=u;
	in[u]=1;
	int v;
	for(int i=hd[u];i!=-1;i=nt[i])
	{
		v=node[i];
		if(e!=-1 && (i^1)==e) continue;
//		cerr<<u<<" "<<v<<endl;
		if(!dfn[v]) tarjan(v,i),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	}
	
	if(dfn[u]==low[u])
	{
		c++;
		while(st[top-1]!=u)
		{
			col[st[top-1]]=c;
			in[st[top-1]]=0;
			top--;
		}
		col[st[top-1]]=c;
		in[st[top-1]]=0;
		top--;		
	}
}

int fa[mxn];

void build()
{
	for(int i=1;i<=c;i++) fa[i]=i;
	
	int x,y,fx,fy;
	for(int i=1;i<=n;i++)
		for(int j=hd[i];j!=-1;j=nt[j])
		{
			x=col[i],y=col[node[j]];
			fx=u_f(x),fy=u_f(y);
			if(fx==fy) continue;
			fa[fx]=fy;
			con(x,y),con(y,x);
		}
}

int f[mxn],dep[mxn];
int ans=0;

void dfs(int u,int fat)
{
	if(!u) return ;
	dep[u]=dep[fat]+1;
	f[u]=dep[u];
	int d1=dep[u],d2=dep[u],v;
	for(int i=hd[u];i!=-1;i=nt[i])
	{
		v=node[i];
		if(!v || v==fat) continue;
		dfs(v,u);
		if(f[v]>d1) d2=d1,d1=f[v];
		else if(f[v]>d2) d2=f[v];
	}
	f[u]=max(f[u],d1);
//	cerr<<u<<" "<<d1<<" "<<d2<<endl;
	ans=max(ans,d1+d2-2*dep[u]);
	return ;
}

void solve()
{
	memset(hd,-1,sizeof hd);
	memset(dfn,0,sizeof dfn);
	fp=0; tim=0; top=0; ans=0;
	c=n;
	int x,y;
	for(int i=0;i<m;i++)
	{
		x=read(),y=read();
		con(x,y),con(y,x);
	}
	
/*	for(int i=1;i<=n;i++)
	{
		cerr<<i<<": ";
		for(int j=hd[i];j!=-1;j=nt[j])
			cerr<<node[j]<<"("<<j<<") ";
		cerr<<endl;
	}
*/	
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,-1);//,cerr<<"###\n";
	build();
	
/*	for(int i=1;i<=n;i++)
		cerr<<i<<": "<<dfn[i]<<" "<<low[i]<<" "<<col[i]<<endl;
*/	
	dfs(n+1,0);
	
//	cerr<<ans<<endl;
	
	printf("%d\n",c-n-1-ans);
}

int main()
{
//	freopen("rebuild.in","r",stdin);
//	freopen("rebuild.out","w",stdout);
	
	n=read(),m=read();
	while(n!=0 && m!=0)
	{
		solve();
		n=read(),m=read();
	}
		
	
	return 0;
}

void con(int x,int y)
{
	node[fp]=y;
	nt[fp]=hd[x];
	hd[x]=fp;
	fp++;
}

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int u_f(int x)
{
	if(x==fa[x]) return x;
	int root=u_f(fa[x]);
	return fa[x]=root;
}
