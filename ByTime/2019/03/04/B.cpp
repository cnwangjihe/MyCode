// Date      : 2019-03-04 16:07:43
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

#define LOG2(X) ((unsigned) (8*sizeof (unsigned int) - __builtin_clzl((X)) - 1))

using namespace std;

const int dx[] = {-1,0,1,0},
		  dy[] = {0,1,0,-1};
const int MAXN = 1009,
		  MAXQ = 300009,
		  MAXP = MAXN*MAXN,
		  MAXM = MAXP*2,
		  INF  = 1000000009;

int _head[MAXP],_node[MAXM],_next[MAXM];
int f[MAXP],s[MAXP],a[MAXP];
int dep[MAXP],p[MAXP];
int jmp[MAXP][30],Min[MAXP][30];
bool _in[MAXP],vis[MAXP];
int fa[MAXP];
int n,q,fp=0;

inline int Id(pair<int,int> a) {return (a.first<1 || a.second<1)?0:(a.first-1)*n+a.second;}
inline int Id(int x,int y) {return (x<1 || y<1)?0:(x-1)*n+y;}
inline pair<int,int> Pos(int id) {return make_pair((id-1)/n+1,(id-1)%n+1);}
inline int GetSum(int sx,int sy,int ex,int ey) {return s[Id(ex,ey)]-s[Id(ex,sy-1)]-s[Id(sx-1,ey)]+s[Id(sx-1,sy-1)];}
inline bool _cmp(int a,int b) {return f[a]>f[b];}

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void Pre()
{
	int rx,ry,lx,ly;
	for (int i=1;i<=n;i++)
		for (int j=1,p=1;j<=n;j++)
		{
			if (!a[Id(i,j)])
				p=0,f[Id(i,j)]=0;
			else
			{
				for (p=max(0,p-1),f[Id(i,j)]=p*2-1;p<=n;p++) 
				{
					rx=min(i+p-1,n),ry=min(j+p-1,n);
					lx=max(i-p+1,0),ly=max(j-p+1,0);
					if (GetSum(lx,ly,rx,ry)==(p*2-1)*(p*2-1))
						f[Id(i,j)]=p*2-1;
					else
					{
						p--;
						break;
					}
				}
			}
		}
/*	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%d ",f[Id(i,j)]);
		putchar('\n');
	}*/
	return ;
}

void Build(int u,int fa)
{
	vis[u]=1;
	int v;
//	cerr << u << endl;
	jmp[u][0]=fa,Min[u][0]=f[u];
	dep[u]=dep[fa]+1;
	for (int i=0;jmp[u][i];i++)
		jmp[u][i+1]=jmp[jmp[u][i]][i],
		Min[u][i+1]=min(Min[u][i],Min[jmp[u][i]][i]);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		Build(v,u);
	}
	return ;
}

int GetMin(int a,int b)
{
	int ans=INF;
	if (dep[a]<dep[b])
		swap(a,b);
	for (int d=dep[a]-dep[b];d;d^=d&-d)
		ans=min(ans,Min[a][LOG2(d&-d)]),a=jmp[a][LOG2(d&-d)];
	if (a==b)
		return min(Min[b][0],ans);
	for (int i=22;~i && jmp[a][0]!=jmp[b][0];i--)
		if (jmp[a][i]!=jmp[b][i])
		{
			ans=min(ans,min(Min[a][i],Min[b][i]));
			a=jmp[a][i],b=jmp[b][i];
		}
	return min(ans,min(Min[a][1],Min[b][0]));
}

int Find(int u)
{
	int x=u,t;
	while (fa[u]!=u)
		u=fa[u];
	while (fa[x]!=x)
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	char c;
	int x,y,v,fx,fy;
	memset(_head,-1,sizeof _head);
	memset(Min,0x7f,sizeof Min);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			do {c=getchar();}
				while (c!='.' && c!='#');
			a[Id(i,j)]=(c=='.');
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			s[Id(i,j)]=s[Id(i,j-1)]-s[Id(i-1,j-1)]+s[Id(i-1,j)]+a[Id(i,j)];
	Pre();
	for (int i=1;i<=Id(n,n);i++)
		fa[i]=i;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			p[Id(i,j)]=Id(i,j);
	sort(p+1,p+Id(n,n)+1,_cmp);
	for (int k=1;k<=Id(n,n);k++)
	{
		int i=p[k];
		x=Pos(i).first,y=Pos(i).second;
	//	printf("%d %d:\n",x,y);
		if (!a[i])
			continue;
		for (int j=0;j<4;j++)
		{
			if (x+dx[j]==0 || x+dx[j]==n+1 || y+dy[j]==0 || y+dy[j]==n+1)
				continue;
			v=Id(x+dx[j],y+dy[j]);
			if (_in[v])
			{
				fx=Find(i),fy=Find(v);
				if (fx==fy)
					continue;
				fa[fx]=fy;
				_connect(i,v),_connect(v,i);
			//	printf("%d %d => %d %d\n",x,y,x+dx[j],y+dy[j]);
			}
		}
		_in[i]=1;
	}
	for (int i=1;i<=Id(n,n);i++)
		if (!vis[i] && a[i])
			Build(i,0);
	scanf("%d",&q);
	int sx,sy,ex,ey;
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		x=Id(sx,sy),y=Id(ex,ey);
	//	cerr << x << ' ' << y << '\n';
		printf("%d\n",Find(x)!=Find(y)?0:GetMin(x,y));
	}
	return 0;
}