#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

const int MAXN = 100003,
		  MAXC = 8;

char s[100003];
int n;

struct SAM
{
	int link[MAXN*2],len[MAXN*2];
	int next[MAXN*2][MAXC];
	int line[MAXN*2];
	bool vis[MAXN*2];
	int cur,last,p,q,clone,tail,head,u,v;
	void clean()
	{
		last=cur=0;
		memset(next,-1,sizeof next);
		memset(link,-1,sizeof link);
		memset(len,0,sizeof len);
		memset(vis,0,sizeof vis);
	}
	SAM() {clean();}
	void copy(int a,int b)
	{
		for (int i=0;i<8;i++)
			next[a][i]=next[b][i];
		link[a]=link[b];
	}
	void add(char c)
	{
		c-='A';
		++cur;
		len[cur]=len[last]+1;
		for (p=last;p!=-1 && next[p][c]==-1;p=link[p])
			next[p][c]=cur;
		if (p==-1)
		{
			link[cur]=0;
			last=cur;
			return ;
		}
		q=next[p][c];
		if (len[p]+1==len[q])
		{
			link[cur]=q;
			last=cur;
			return ;
		}
		clone=cur+1;
		copy(clone,q);
		len[clone]=len[p]+1;
		link[cur]=clone;
		link[q]=clone;
		for (;(~p) && next[p][c]==q;p=link[p])
			next[p][c]=clone;
		last=cur++;
		return ;
	}
	void _out(int u,int v)
	{
		n=0;
		s[n++]=v+'A';
		for (int i=link[u];~i;i=link[i])
		{
			for (int j=0;j<8;j++)
				if (next[i][j]==u)
				{
					s[n++]=j+'A';
					break;
				}
			u=i;
		}
		for (int i=n-1;~i;i--)
			putchar(s[i]);
		putchar('\n');
		return ;
	}
	void BFS()
	{
		memset(link,-1,sizeof link);
		tail=head=0;
		line[tail++]=0;
		vis[0]=1;
		while (head!=tail)
		{
			u=line[head++];
			for (int i=0;i<8;i++)
			{
				if (next[u][i]==-1)
				{
					_out(u,i);
					return ;
				}
				if (!vis[next[u][i]])
				{
					line[tail++]=next[u][i];
					link[next[u][i]]=u;
					vis[next[u][i]]=1;
				}
			}
		}
	}
}sam;

int main()
{
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
//	printf("%d\n",sizeof sam+sizeof s);
	for (;ttt;ttt--)
	{
		n=0;
		sam.clean();
		do {s[0]=getchar();}
			while (s[0]<'A' || s[0]>'H');
		do {s[++n]=getchar();}
			while (s[n]>='A' && s[n]<='H');
		for (int i=0;i<n;i++)
			sam.add(s[i]);
		sam.BFS();
	}
	return 0;
}