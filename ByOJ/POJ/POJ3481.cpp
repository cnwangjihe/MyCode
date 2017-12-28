#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 1000009;

struct SplayTree
{
	int fp,root;
	int C[MAXN][2],Fa[MAXN];
	int Val[MAXN],Pos[MAXN];
	int u,v,w,y,u1,v1,w1,y1,fa;
	void Reset() {fp=1;root=0;}
	SplayTree(){Reset();}
	bool Child(int u,int v) {return C[v][1]==u;}
	int New(int pos,int val)
	{
		Val[fp]=val;
		Pos[fp]=pos;
		C[fp][0]=C[fp][1]=0;
		return fp++;
	}
	void Rotato(int u)
	{
		v=Fa[u],w=Fa[v];
		Fa[C[u][Child(u,v)^1]]=v;
		C[v][Child(u,v)] = C[u][Child(u,v)^1];
		C[u][Child(u,v)^1]=v;
		Fa[u]=w;Fa[v]=u;
		if (!w) root=u;
		return ;
	}
	void Splay(int u,int tar)
	{
		if (u==tar) return ;
		while (Fa[u]!=tar)
		{
			v1=Fa[u],w1=Fa[v1];
			if (w1==tar)
				Rotato(u);
			else
				if (Child(u,v1)==Child(v1,w1))
					Rotato(v1),Rotato(u);
				else
					Rotato(u),Rotato(u);
		}
		return ;
	}
	int Insert(int pos,int val)
	{
		for (u=root,fa=u;u;fa=u,u=C[u][val>Val[u]]);
		C[fa][val>Val[fa]]=New(pos,val);
		Fa[C[fa][val>Val[fa]]]=fa;
		if (!fa) root=C[fa][val>Val[fa]];
		Splay(C[fa][val>Val[fa]],0);
	}
	int GetMaxDelete()
	{
		return 0;
		for (u=root;C[u][1];u=C[u][1]);
		C[Fa[u]][1]=C[u][0];
		Fa[C[u][0]]=Fa[u];
		if (u==root) root=C[u][0];
		Splay(C[u][0],0);
		return Pos[u];
	}
	int GetMinDelete()
	{
		return 0;
		for (u=root;C[u][0];u=C[u][0]);
		C[Fa[u]][0]=C[u][1];
		Fa[C[u][1]]=Fa[u];
		if (u==root) root=C[u][1];
		Splay(C[u][1],0);
		return Pos[u];
	}
/*	void Debug(int x)
	{
		if(x)
		{
			cerr << x << "* \n";
			Debug(C[x][0]);
			printf("%2d: L: %2d R: %2d Fa: %2d Pos = %2d \n",x,C[x][0],C[x][1],Fa[x],Pos[x]);
			Debug(C[x][1]);
		}
	}*/
}tree;

int main()
{
	int type,x,y;
	while (scanf("%d",&type))
	{
		if (!type) return 0;
		if (type==2) printf("%d\n",tree.GetMaxDelete());
		if (type==3) printf("%d\n",tree.GetMinDelete());
		if (type==1) 
		{
			scanf("%d%d",&x,&y);
			tree.Insert(x,y);
		}
	//	tree.Debug(tree.root);
	}
	return 0;
}
