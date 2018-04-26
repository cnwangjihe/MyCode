#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 1000009;

int n,m,fp=0,root=0;

struct Tnode { int v,lc,rc,h,fa; bool _in;};

Tnode tree[MAXN];

inline bool Cmp(int A,int B)
{
	return tree[A].v==tree[B].v?A<B:tree[A].v<=tree[B].v;
}

inline void Up(int u)
{
	tree[u].h=(tree[u].rc)?(tree[tree[u].rc].h+1):0;
	tree[tree[u].lc].fa=tree[tree[u].rc].fa=u;
}

int Build(int x)
{
	tree[++fp].v=x;
	tree[fp].h=tree[fp].lc=tree[fp].rc=0;
	tree[fp].fa=fp;
	tree[fp]._in=1;
	return fp;
}

int GetRoot(int u)
{
	return tree[u].fa==u?u:GetRoot(tree[u].fa);
}

int Merge(int A,int B)
{
	tree[A].fa=A;
	tree[B].fa=B;
	if (!A) return B;
	if (!B) return A;
	if (!Cmp(A,B)) 
		swap(A,B);
	tree[A].rc=Merge(tree[A].rc,B);
	if (tree[tree[A].lc].h<tree[tree[A].rc].h)
		swap(tree[A].lc,tree[A].rc);
	Up(A);
	return A;
} 

void Insert(int u,int x)
{
	u=GetRoot(u);
	x=Build(x);
	if (!u)
		return ;
	Merge(u,x);
	return ;
} 

int GetMin(int u)
{
	u=GetRoot(u);
	return tree[u].v;
}

void Del(int u)
{
	u=GetRoot(u);
	tree[u]._in=0;
	Merge(tree[u].lc,tree[u].rc);
	return ;
}

int main()
{
//	freopen("tmp.in","r",stdin);
//	freopen("tmp.out","w",stdout);
	int x,y,type;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&x);
		Build(x);
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d",&type);
		if (type-1)
		{
			scanf("%d",&x);
			if (!tree[x]._in) 
				printf("-1\n");
			else
				printf("%d\n",GetMin(x)),Del(x);
		}
		else
		{
			scanf("%d%d",&x,&y);
			if (tree[x]._in && tree[y]._in)
			{
				x=GetRoot(x);y=GetRoot(y);
				Merge(x,y);
			}
		}
	}
	return 0;
}
