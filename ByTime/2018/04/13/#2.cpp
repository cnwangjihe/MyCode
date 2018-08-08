#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int maxn=100100;
const int oo=1000000007;

struct edge
{
	int obj;
	edge *Next;
} e[maxn<<1];
edge *head[maxn];
int cur;

int Size[maxn];
int max_Size[maxn];

int tree[maxn];
int num;

int of[maxn];
int og[maxn];
int cf[maxn];
int cg[maxn];

int val[maxn];
bool vis[maxn];
int n,ans;

void Add(int x,int y)
{
	cur++;
	e[cur].obj=y;
	e[cur].Next=head[x];
	head[x]=e+cur;
}

void Dfs(int node,int fa)
{
	tree[++num]=node;
	Size[node]=1;
	max_Size[node]=0;
	for (edge *p=head[node]; p; p=p->Next)
	{
		int son=p->obj;
		if ( vis[son] || son==fa ) continue;
		Dfs(son,node);
		Size[node]+=Size[son];
		max_Size[node]=max(max_Size[node],Size[son]);
	}
}

void Get_Size(int node,int fa)
{
	Size[node]=1;
	for (edge *p=head[node]; p; p=p->Next)
	{
		int son=p->obj;
		if ( vis[son] || son==fa ) continue;
		Get_Size(son,node);
		Size[node]=max(Size[node],Size[son]+1);
	}
}

void Work1(int node,int fa,int R,int L,int Max)
{
	if (val[node]==1)
		if (R) R--; else L++;
	else R++;
	Max=max(val[node]+Max,0);
	if (!R) of[L]=max(of[L],Max);
	
	for (edge *p=head[node]; p; p=p->Next)
	{
		int son=p->obj;
		if ( vis[son] || son==fa ) continue;
		Work1(son,node,R,L,Max);
	}
}

void Work2(int node,int fa,int R,int L,int Max,int Sum)
{
	if (val[node]==-1)
		if (L) L--; else R++;
	else L++;
	Sum+=val[node];
	Max=max(Sum,Max);
	if (!L) og[R]=max(og[R],Max);
	
	for (edge *p=head[node]; p; p=p->Next)
	{
		int son=p->obj;
		if ( vis[son] || son==fa ) continue;
		Work2(son,node,R,L,Max,Sum);
	}
}

void Solve(int node)
{
	num=0;
	Dfs(node,node);
	if (num==1) return;
	
	int root=node;
//	if (root==7)
//		root=8;
	for (int i=1; i<=num; i++)
	{
		int x=tree[i];
		max_Size[x]=max(max_Size[x],Size[node]-Size[x]);
		if (max_Size[x]<max_Size[root]) root=x;
	}
	
	for (int i=0; i<=num; i++) cf[i]=cg[i]=-oo;
	int x=0,y=0;
	cg[0]=0;
	if (val[root]==1) cf[1]=1,y++; else x++;
//	cerr << num << endl;
	for (edge *p=head[root]; p; p=p->Next)
	{
		int son=p->obj;
		if (vis[son]) continue;
		
		Get_Size(son,root);
		Size[son]+=2;
		for (int i=0; i<=Size[son]; i++) of[i]=og[i]=-oo;
		
		Work1(son,root,x,y,y);
		Work2(son,root,0,0,0,0);
		
		for (int i=0; i<=Size[son]; i++)
		{
	//		if (root==8)
	//			cerr << of[i] << ' '<< cf[i] << ' '<< og[i] << ' '<< cg[i] << '\n';
			
			if ( cf[i]>=0 && og[i]>=0 ) ans=max(ans, max(cf[i],i+og[i]) );
			if ( of[i]>=0 && cg[i]>=0 ) ans=max(ans, max(of[i],i+cg[i]) );
		}
		for (int i=0; i<=Size[son]; i++) cf[i]=max(cf[i],of[i]),cg[i]=max(cg[i],og[i]);
	}
	
	vis[root]=1;
	for (edge *p=head[root]; p; p=p->Next)
	{
		int son=p->obj;
		if (vis[son]) continue;
		Solve(son);
	}
}

int main()
{
	freopen("2443.in","r",stdin);
	freopen("#2.out","w",stdout);
	
	n=0;
	scanf("%d",&n);
	while (n)
	{
		cur=-1;
		for (int i=1; i<=n; i++) head[i]=NULL,vis[i]=0;
		for (int i=1; i<=n; i++)
		{
			int x;
			scanf("%d%d",&x,&val[i]);
			if (x) Add(x,i),Add(i,x);
		}
		
		ans=0;
		Solve(1);
		printf("%d\n",ans);
		
		n=0;
		scanf("%d",&n);
	}
	
	return 0;
}



























