#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN=301000;
const int MOD=1000000007;

struct Edge
{
	int x;Edge *nex;
	Edge(int x1=0,Edge *n1=0):x(x1),nex(n1){}
} *E[MAXN],ESpace[MAXN*2];
int ESpaceCnt;
void Insert(int x,int y);

int n,m;
int Fa[MAXN][30];
int H[MAXN],Low[MAXN];
int que[MAXN],qhead,qtail;
bool vis[MAXN];

int UFa[MAXN];
int R[MAXN];
int Cnt;

void BFS();
int GetLCA(int x,int y);

int GetFa(int x);
void Merge(int x,int y,int z);

void Build();

void OutZero();

int Pow(int k);

int ReadInt();

int main()
{
	freopen("2627.in","r",stdin);
	freopen("#1.out","w",stdout);

	n=ReadInt();m=ReadInt();
	for (int i=1;i<n;++i)
	{
		int x,y;
		x=ReadInt();y=ReadInt();
		Insert(x,y);
		Insert(y,x);
	}
	BFS();
	for (int i=1;i<=n;++i) UFa[i]=i,Low[i]=H[i];
	for (int i=1;i<=m;++i)
	{
		int x,y,z;
		x=ReadInt();y=ReadInt();
		z=GetLCA(x,y);
		if (z!=x && z!=y) Merge(x,y,1);
		Low[x]=min(Low[x],H[z]);
		Low[y]=min(Low[y],H[z]);
	}
	Build();
	printf("%d\n",Pow(n-1-Cnt));

	return 0;
}
void BFS()
{
	que[0]=1;qhead=0;qtail=1;vis[1]=1;H[1]=1;
	while (qhead<qtail)
	{
		int x=que[qhead++];
		for (Edge* i=E[x];i;i=i->nex)
		{
			int y=i->x;
			if (vis[y])continue;
			Fa[y][0]=x;
			vis[y]=1;
			H[y]=H[x]+1;
			que[qtail++]=y;
		}
	}
	for (int i=0;i<n;++i)
	{
		int x=que[i];
		for (int j=0;Fa[Fa[x][j]][j];++j)
			Fa[x][j+1]=Fa[Fa[x][j]][j];
	}
}
int GetLCA(int x,int y)
{
	if (H[x]<H[y]) swap(x,y);
	int k=H[x]-H[y];
	for (int i=0;k>0;k>>=1,i++)
		if (k&1) x=Fa[x][i];
	for (k=0;Fa[x][k];++k);	
	while (x!=y)
	{
		while (k!=0 && Fa[x][k]==Fa[y][k]) --k;
		x=Fa[x][k];
		y=Fa[y][k];
	}
	return x;
}

int GetFa(int x)
{
	if (UFa[x]==x) return x;
	int y=GetFa(UFa[x]);
	R[x]^=R[UFa[x]];
	UFa[x]=y;
	return y;
}
void Merge(int x,int y,int z)
{
	int x1=GetFa(x),y1=GetFa(y);
	if (x1==y1)
		if ((R[x]^R[y])==z) return;
		else OutZero();
	UFa[x1]=y1;
	R[x1]=z^R[x]^R[y];
	Cnt++;
}
void Build()
{
	for (int j=n-1;j>=0;--j)
	{
		int x=que[j];
		vis[x]=0;
		for (Edge* i=E[x];i;i=i->nex)
		{
			int y=i->x;
			if (vis[y]) continue;
			Low[x]=min(Low[x],Low[y]);
		}
		if (Low[x]+1<H[x]) Merge(x,Fa[x][0],0);
	}
}
void OutZero()
{
	printf("0\n");
	exit(0);
}
int Pow(int k)
{
	LL ans=1;
	for (LL x=2;k>0;k>>=1,x=x*x%MOD)
		if (k&1) ans=ans*x%MOD;
	return int(ans);
}
int ReadInt()
{
	char c=getchar();int num=0;
	while (c<'0' || c>'9') c=getchar();
	while (c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
	return num;
}
void Insert(int x,int y)
{
	Edge *P=&ESpace[++ESpaceCnt];
	*P=Edge(y,E[x]);E[x]=P;
}

