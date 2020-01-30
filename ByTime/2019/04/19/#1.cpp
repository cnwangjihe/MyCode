#include <bits/stdc++.h>
using namespace std;

const int mx=1e6+10;
int n,q;
int hd[mx],nt[mx*2],nd[mx*2],len[mx*2],fp=0;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}
void con(int x,int y,int z)
{
	nd[fp]=y;
	nt[fp]=hd[x];
	hd[x]=fp;
	len[fp]=z;
	fp++;
}

int dep[mx],size[mx],dfn[mx],id[mx],tim=0;
int val[mx],sum[mx];
void dfs(int u,int fat)
{
	if(!u) return ;
	dfn[u]=++tim,id[tim]=u;
	dep[u]=dep[fat]+1;
	if(!(dep[u]&1)) val[u]=-val[u];
	sum[u]=val[u]+sum[fat];
	size[u]=1;
	int v;
	for(int i=hd[u];i!=-1;i=nt[i])
	{
		v=nd[i];
		if(!v || v==fat) continue;
		val[v]=len[i];
		dfs(v,u);
		size[u]+=size[v];
	}
}
int tree[mx];
int lowbit(int x){ return x&(-x); }
void add(int p,int v){ for(int i=p;i<=n && i;i+=lowbit(i)) tree[i]+=v; }
int ask(int p){ int ret=0; for(int i=p;i>0;i-=lowbit(i)) ret+=tree[i]; return ret; }

int main()
{
//	freopen("equation.in","r",stdin);
//	freopen("equation.out","w",stdout);
	
	memset(hd,-1,sizeof hd);
	
	n=read(),q=read();
	int x,y;
	for(int i=2;i<=n;i++)
	{
		x=read(),y=read();
		con(i,x,y),con(x,i,y);
	}
	
	dfs(1,0);
	for(int i=1;i<=n;i++) add(i,sum[id[i]]-sum[id[i-1]]);
	int opt,z;
	int t1,t2,t3;
	for(int i=0;i<q;i++)
	{
		opt=read();
		if(opt==1)
		{
			x=read(),y=read(),z=read();
			t1=ask(dfn[x]),t2=ask(dfn[y]);
			if(!(dep[x]&1)) t1=-t1;
			if(!(dep[y]&1)) t2=-t2;
			if((dep[x]&1)^(dep[y]&1))
				if(t1+t2!=z) printf("none\n");
				else printf("inf\n");
			else
			{
				t3=((dep[x]&1)?-1:1)*(t1+t2-z);
				if(t3&1) printf("none\n");
				else printf("%d\n",t3>>1);
			}
		}
		else
		{
			x=read(),y=read();
			if(!(dep[x]&1)) y=-y;
			add(dfn[x],y-val[x]); add(dfn[x]+size[x],val[x]-y);
			val[x]=y;
		}
//		for(int j=1;j<=n;j++) cerr<<ask(dfn[j])<<" "; cerr<<endl;
	}
	
	
	return 0;
}
