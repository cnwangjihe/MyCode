#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000009,
		  MAXC = 30;

struct SAM
{
	int link[MAXN*2],len[MAXN*2];
	int size[MAXN*2];
	int next[MAXN*2][MAXC];
	long long f[MAXN*2];
	int _head[MAXN*2],_next[MAXN*2],_node[MAXN*2];
	long long ans;
	bool vis[MAXN*2];
	int cur,last,fp;
	SAM()
	{
		last=cur=fp=0;
		ans=0;
		memset(next,-1,sizeof next);
		memset(link,-1,sizeof link);
		memset(_head,-1,sizeof _head);
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
		++cur;
		size[cur]=1;
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
	void connect(int a,int b)
	{
		_next[fp]=_head[a];
		_node[fp]=b;
		_head[a]=fp++;
		return ;
	}
	void buildlink()
	{
		for (int i=0;i<=cur;i++)
			if (~link[i])
				connect(link[i],i);
		return ;
	}
	int calc(int u,int v)
	{
	//	if (vis[u])
	//		return size[u];
	//	size[u]=1;
	//	vis[u]=1;
		for (int i=_head[u];~i;i=_next[i])
			size[u]+=calc(_node[i],u);
		ans+=1ll*size[u]*(size[u]-1)*(len[u]-len[v]);
		return size[u];
	}
/*	long long calc(int u)
	{
	//	if (vis[u])
	//		return f[u];
		long long tmp=0;
	//	vis[u]=1;
		for (int i=_head[u];~i;i=_next[i])
		{
			tmp+=calc(_node[i]);
			size[u]+=size[_node[i]];
		}
		f[u]=1ll*size[u]*(size[u]-1)-tmp;
		ans+=f[u]*len[u];
		return f[u];
	}
	*/
};

SAM sam;
char s[MAXN];
int n,q;

int main()
{
	int t,k;
	scanf("%s",s);
	n=strlen(s);
	for (int i=n-1;i>=0;i--)
		sam.add(s[i]);
	sam.buildlink();
	sam.calc(0,sam.cur+1);
	printf("%lld\n",1ll*(n-1)*n*(n+1)/2-sam.ans);
	return 0;
}
