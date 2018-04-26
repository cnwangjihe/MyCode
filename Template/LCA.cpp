#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

/*
struct Tnode{
	int rt,lf,deep,jump[105];
	Tnode(){
		rt=lf=deep=0;
		memset(jump,0,sizeof jump);
	}
};

Tnode Tree[10005];
int N,M,Root;
int pow_2[10005],pow_2_num[10005];

void Build(int root,int fa,int deep)
{
	if (root==0) return;
	Tree[root].deep=deep;
	Tree[root].jump[0]=fa;
	for (int k=1;Tree[root].jump[k-1]!=0;k++)
		Tree[root].jump[k]=Tree[Tree[root].jump[k-1]].jump[k-1];
	Build(Tree[root].lf,root,deep+1);
	Build(Tree[root].rt,root,deep+1);
}
*/

void dfs(int root,int fa,int v)
{
	deep[root]=deep[fa]+1;
	f[root]=1;
	jump[root][0]=fa;
	Max[root][0]=v;
	for (int i=1;i<=18 && jump[root][i-1]!=0;i++)
		jump[root][i]=jump[jump[root][i-1]][i-1],
		Max[root][i]=max(Max[root][i-1],Max[jump[root][i-1]][i-1]);
	for (int i=head[root];i!=-1;i=_next[i])
		if (!f[node[i]]) dfs(node[i],root,val[i]);
	return ;
}

int LCA(int a,int b)
{
	if (deep[a]<deep[b]) swap(a,b);
	int tmp,ans=0;
	if (deep[a]!=deep[b])
		for (tmp=log2(deep[a]-deep[b]);deep[a]!=deep[b];tmp--)
			if (deep[jump[a][tmp]]>=deep[b]) 
				ans=max(ans,Max[a][tmp]),a=jump[a][tmp];
	if (a==b) return ans;
	for (tmp=log2(deep[a]);jump[a][0]!=jump[b][0];tmp--)
		if (jump[a][tmp]!=jump[b][tmp])
			ans=max(ans,max(Max[b][tmp],Max[a][tmp])),
			a=jump[a][tmp],b=jump[b][tmp];
	return max(ans,max(Max[a][0],Max[b][0]));
}
/*
int main()
{
	cin >> N >> Root >> M;
	for (int i=1;i<=N;i++) cin >> Tree[i].lf >> Tree[i].rt;
	pow_2[1]=0; pow_2_num[1]=1;
	for (int i=2;i<=N;i++) pow_2[i]=pow_2[i/2]+1 , pow_2_num[i]=pow_2_num[i/2]*2;
	Build(Root,0,1);
	for (int i=0;i<M;i++)
	{
		int a,b;
		cin >> a >> b;
		cout << LCA(a,b) << endl;
	}
}
*/