#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 500009,
		  MAXC = 30;

struct SAM
{
	int link[MAXN*2],len[MAXN*2];
	int f[MAXN*2],size[MAXN*2],ton[MAXN*2],ti[MAXN*2];
	int next[MAXN*2][MAXC];
	bool vis[MAXN*2];
	int cur,last;
	SAM()
	{
		last=cur=0;
		memset(next,-1,sizeof next);
		memset(link,-1,sizeof link);
		memset(vis,0,sizeof vis);
		memset(len,0,sizeof len);
	}
	void copy(int a,int b)
	{
		for (int i=0;i<26;i++)
			next[a][i]=next[b][i];
		link[a]=link[b];
	}
	void add(char c)
	{
		int p,q,clone;
		c-='a';
		++cur;size[cur]=1;
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
	void pre(int t)
	{
		builds(t);
		buildf(0);
	}
	void builds(int t)
	{
		for (int i=0;i<=cur;i++) ton[len[i]]++;
		for (int i=1;i<=MAXN*2;i++) ton[i]+=ton[i-1];
		for (int i=0;i<=cur;i++) ti[--ton[len[i]]]=i;
		for (int i=cur;~i;i--)
			if (~link[ti[i]])
			{
				if (t)
					size[link[ti[i]]]+=size[ti[i]];
				else size[ti[i]]=1;
			}
		return ;
	}
	int buildf(int u)
	{
		if (vis[u])
			return f[u];
		vis[u]=1;
		f[u]=size[u];
		for (int i=0;i<26;i++)
			if (~next[u][i]) 
				f[u]+=buildf(next[u][i]);
		return f[u];
	}
	void find(int u,int n)
	{
		if (u) n-=size[u];
		if (n<=0) return; 
		for (int i=0;i<26;i++)
		{
			if (next[u][i]==-1) 
				continue;
			if (n<=f[next[u][i]])
			{
				putchar(i+'a');
				find(next[u][i],n);
				return ;
			}
			n-=f[next[u][i]];
		}
		return ;
	}
};

SAM sam;
char s[MAXN];
int n,q;

int main()
{
	int t,k;
	scanf("%s",s);
	n=strlen(s);
	for (int i=0;i<n;i++)
		sam.add(s[i]);
	scanf("%d%d",&t,&k);
	sam.pre(t);
	if (sam.f[0]-sam.size[0]<k)
		puts("-1");
	else
		sam.find(0,k);
	return 0;
}
