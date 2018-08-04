#include <bits/stdc++.h>

using namespace std;

struct Tnode
{
	int v,len,from;
	Tnode(){}
	Tnode(int a,int b,int c):v(a),len(b),from(c){}
};

bool _cmp(Tnode a,Tnode b){return a.v<b.v;}

void getroot(int u,int fa,int s)
{
	size[u]=1;
	Max[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || fa==v)
			continue;
		getroot(v,u);
		Max[u]=max(Max[u],size[v],s);
		size[u]+=size[v];
	}
	Max[u]=max(Max[u],s-size[u]);
	if (Max[u]<Max[root])
		root=u;
	return ;
}

int getsize(int u,int fa)
{
	size[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v==fa)
			continue;
		size[u]+=getsize(v,u);
	}
	return size[u];
}

void dfs(int u,int fa,int from,int Max,int len)
{
	Max=max(Max,a[u]);
	len++;
	t[fp++]=Tnode(Max,len,from);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v=fa)
			continue;
		dfs(v,u,from,Max,len);
	}
	return ;
}

void solve(int u,int s)
{
	root=u;
	getroot(u,0,s);
	u=root;
	getsize(root,0);
	done[root]=1;
	for (int )
}

int main()
{

}