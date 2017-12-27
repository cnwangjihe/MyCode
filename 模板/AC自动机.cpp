/*简单来说,就是先将一堆短串建字典树,然后整体跑一次树上kmp*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Tnode
{
	int fail,f;
	int _next[26];
	void clean()
	{
		memset(_next,0,sizeof _next);
		fail=f=0;/*f使本模板成为了一次性用品(f被-1,只能查找一次)*/
	}
	Tnode() {clean();}
};
struct Tac
{
	Tnode tree[500000];
	char c[60],tar[1000005];
	int len,fp,tlen;
	int line[1000003];
	void clean()
	{
		for (int i=0;i<=500000;i++) tree[i].clean();
		for (int i=0;i<26;i++) 
			tree[0]._next[i]=1; /*不知道怎么想的，但可以在fail里的while少一个判断*/
		fp=2; /*温馨提示：tree[0]&&[1]都没用(好弱...)*/
	}
	Tac(){clean();}
	void insert()
	{
		int now=1;
		for (int i=0;i<len;i++)
		{
			if (tree[now]._next[int(c[i])-int('a')]==0)
				tree[now]._next[int(c[i])-int('a')]=fp++;
			now=tree[now]._next[int(c[i])-int('a')];
		}
		tree[now].f++;
		return ;
	}/*建字典树*/
	void buildfail()
	{
		int now,head=0,tail=0,u,k;
		line[tail++]=1;
		while (head<tail)
		{
			now=line[head++];
			for (int i=0;i<26;i++) /*对now的每个子树建fail*/
			{
				if (tree[now]._next[i])
				{
					u=tree[now]._next[i];
					k=tree[now].fail;
					while (!tree[k]._next[i]) k=tree[k].fail; /*fail到匹配或0*/
					tree[u].fail=tree[k]._next[i];
					line[tail++]=u; /*并不会重复入队所以没有f*/ 
				//	cerr << tree[u].fail <<' ';
				}
			}
		}/*bfs跑kmp，然而常数非常大*/ 
	}
	int solve() /*tar==target*/
	{
		int root=1,ch,ans=0,tmp;/*root==now*/
		for (int i=0;i<tlen;i++)
		{
			ch=int(tar[i])-int('a');
			while (root && (!tree[root]._next[ch])) root=tree[root].fail;
			if (root!=0) root=tree[root]._next[ch];
				else root=1;
			tmp=root; /*以防万一*/
			while (tmp!=1) 
			{
				if (tree[tmp].f==-1) break;
				ans+=tree[tmp].f;
				tree[tmp].f=-1; /*找过就不用再来了(小心清零问题)*/
				tmp=tree[tmp].fail;
			}
		}
		return ans;
	}
}ac;

int ttt,n;

int main()
{
	scanf("%d",&ttt);
	for (;ttt>0;ttt--)
	{
		ac.clean();
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			do
				{ac.c[0]=getchar();}
			while (ac.c[0]<'a' || ac.c[0]>'z');
			ac.len=1;
			
			do
				{ac.c[ac.len++]=getchar();}
			while (ac.c[ac.len-1]>='a' && ac.c[ac.len-1]<='z');
			ac.len--;
			
			ac.insert();
		}
		ac.buildfail();
		do
			{ac.tar[0]=getchar();}
		while (ac.tar[0]<'a' || ac.tar[0]>'z');
		ac.tlen=1;
		
		do
			{ac.tar[ac.tlen++]=getchar();}
		while (ac.tar[ac.tlen-1]>='a' && ac.tar[ac.tlen-1]<='z');
		ac.tlen--;
		
		printf("%d\n",ac.solve());
	}
}