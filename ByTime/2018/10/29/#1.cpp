#include <bits/stdc++.h>
using namespace std;

const int oo=1000000000;
const int mxn=10005;
const int mxm=60005;
int n,m,q;
struct Tline
{
	int x,y,z;
};
Tline line[mxm];
int hd[mxn],node[mxn*2],nt[mxn*2],len[mxn*2],fp=0;
int fa[mxn];
int dep[mxn],table[mxn][16],tmin[mxn][16];

int u_f(int x)
{
	if(x==fa[x]) return x;
	int root=u_f(fa[x]);
	return fa[x]=root;
}

void con(int x,int y,int z)
{
	node[fp]=y;
	nt[fp]=hd[x];
	hd[x]=fp;
	len[fp]=z;
	fp++;
}

bool cmp(Tline x,Tline y)
{
	return x.z>y.z;
}

void dfs(int u,int fat)
{
	if(!u) return ;
	dep[u]=dep[fat]+1;
	for(int i=1;i<16;i++)
	{
		table[u][i]=table[table[u][i-1]][i-1];
		tmin[u][i]=min(tmin[u][i-1],tmin[table[u][i-1]][i-1]);
//		cerr<<i<<": "<<tmin[2][0]<<endl;
	}		

//	cerr<<u<<" "<<table[u][0]<<" "<<tmin[u][0]<<endl;

	int v;
	for(int i=hd[u];i!=-1;i=nt[i])
	{
		v=node[i];
		if(!v || v==fat) continue;
		table[v][0]=u;
		tmin[v][0]=len[i];
		dfs(v,u);
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	
//	cerr<<x<<" "<<y<<endl;
	int ans=oo;
	for(int i=15;i>=0;i--)
		if(dep[table[x][i]]>=dep[y]) ans=min(ans,tmin[x][i]),x=table[x][i];
	
//	cerr<<ans<<endl;
	if(x==y) return ans;
	for(int i=15;i>=0;i--)
		if(table[x][i]!=table[y][i])
			ans=min(ans,min(tmin[x][i],tmin[y][i])),x=table[x][i],y=table[y][i];
	ans=min(ans,min(tmin[x][0],tmin[y][0]));
	return ans;
}

int main()
{
	freopen("Trouble.in","r",stdin);
	freopen("Trouble.out","w",stdout);
	
	memset(hd,-1,sizeof hd);
	
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
		scanf("%d%d%d",&line[i].x,&line[i].y,&line[i].z);
	
	sort(line,line+m,cmp);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	
	for(int i=0;i<m;i++)
	{
		int fx=u_f(line[i].x),fy=u_f(line[i].y);
		if(fx==fy) continue;
		fa[fx]=fy;
		con(line[i].x,line[i].y,line[i].z);
		con(line[i].y,line[i].x,line[i].z);
//		cerr<<line[i].x<<" "<<line[i].y<<" "<<line[i].z<<endl;
	}
	
	for(int i=1;i<=n;i++)
		if(u_f(i)==i) dfs(i,0);

	
//		cerr<<tmin[2][0]<<"##\n";
	scanf("%d",&q);
	int x,y;
	for(int i=0;i<q;i++)
	{
		scanf("%d%d",&x,&y);
//		cerr<<tmin[2][0]<<"##\n";
		if(u_f(x)!=u_f(y))
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n",lca(x,y));
	}
	
	
	return 0;
}
