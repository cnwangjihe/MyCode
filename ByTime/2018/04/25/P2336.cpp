#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

const int MAXN = 100009;

map <int,int> Next[MAXN*2];
int Link[MAXN*2],len[MAXN*2],siz[MAXN*2];
int ans[MAXN],pre[MAXN*2],mark[MAXN*2];
int len1[MAXN],len2[MAXN],s[MAXN];
int n,m,cur=0,last=0;

void Copy(int u,int v)
{
	Next[v]=Next[u];
	Link[v]=Link[u];
	return ;
}

void Insert(int c)
{
	int p,q;
	cur++;
	len[cur]=len[last]+1;
	for (p=last;(~p) && !Next[p].count(c);p=Link[p])
		Next[p][c]=cur;
	last=cur;
	if (p==-1)
	{
		Link[cur]=0;
		return ;
	}
	q=Next[p][c];
	if (len[p]+1==len[q])
	{
		Link[cur]=q;
		return ;
	}
	int clone=cur+1;
	Copy(q,clone);
	len[clone]=len[p]+1;
	Link[q]=clone;
	Link[cur]=clone;
	for (;(~p) && Next[p].count(c) && Next[p][c]==q;p=Link[p])
		Next[p][c]=clone;
	cur++;
	return ;
}

void Up1(int u,int id)
{
	for (;(~u) && pre[u]!=id;u=Link[u])
	{
		pre[u]=id;
		siz[u]++;
	}
	return ;
}

void Up2(int u,int id)
{
	for (;(~u) && pre[u]!=id;u=Link[u])
	{
		pre[u]=id;
		ans[id]+=mark[u];
	}
	return ;
}


void solve1()
{
	int cnt=0,u;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		last=0;
		scanf("%d",&len1[i]);
		for (int j=0;j<len1[i];j++)
		{
			scanf("%d",&s[cnt]);
			Insert(s[cnt++]);
		}
		last=0;
		scanf("%d",&len2[i]);
		for (int j=0;j<len2[i];j++)
		{
			scanf("%d",&s[cnt]);
			Insert(s[cnt++]);
		}
	}
	memset(pre,0,sizeof pre);
	cnt=0;
	for (int i=1;i<=n;i++)
	{
		u=0;
		for (int j=0;j<len1[i];j++)
			Up1(u=Next[u][s[cnt++]],i);
		u=0;
		for (int j=0;j<len2[i];j++)
			Up1(u=Next[u][s[cnt++]],i);
	}
	return ;
}

void solve2()
{
	int u,flag,len3,a;
	for (int i=0;i<m;i++)
	{
		u=0;flag=1;
		scanf("%d",&len3);
		for (int i=0;i<len3;i++)
		{
			scanf("%d",&a);
		//	cerr << Next[u][a] << "s \n";
			if (flag && !Next[u].count(a))
				flag=0;
			else
				u=Next[u][a];
		}
		if (flag)
		{
//			cerr << u << endl;
			printf("%d\n",siz[u]);
			mark[u]++;
		}
		else
			printf("0\n");
	}
	int cnt=0;
	memset(pre,0,sizeof pre);
	for (int i=1;i<=n;i++)
	{
		u=0;
		for (int j=0;j<len1[i];j++)
			Up2(u=Next[u][s[cnt++]],i);
		u=0;
		for (int j=0;j<len2[i];j++)
			Up2(u=Next[u][s[cnt++]],i);
	}
	for (int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	putchar('\n');
	return ;
}

int main()
{
	memset(ans,0,sizeof ans);
	memset(Link,-1,sizeof Link);
	solve1();
	solve2();
	return 0;
}