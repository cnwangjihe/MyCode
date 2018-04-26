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
	int next[MAXN*2][MAXC];
	bool end[MAXN*2];
	int cur,last;
	SAM()
	{
		last=cur=0;
		memset(next,-1,sizeof next);
		memset(link,-1,sizeof link);
		memset(end,0,sizeof end);
		memset(len,0,sizeof len);
	}
	void copy(int a,int b)
	{
		for (int i=0;i<26;i++)
			next[a][i]=next[b][i];
		link[a]=link[b];
		end[a]=end[b];
	}
	void add(char c)
	{
		int p,q,clone;
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
	bool issub(char s[],int n)
	{
		int p,t=0;
		for (p=0;p<n && t!=-1 && next[t][s[p]-'A']!=-1;t=next[t][s[p]-'A'],p++);
		return p==n;
	}
};

SAM sam;
char s[MAXN];
int n,q;

int main()
{
	scanf("%s",s);
	n=strlen(s);
	cerr << n << endl;
	for (int i=0;i<n;i++)
		sam.add(s[i]);
/*	for (int i=0;i<2*n;i++)
	{
		for (int j=0;j<26;j++)
			printf("%d ",sam.next[i][j]);
		putchar('\n');
	}
*/	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%s",s);
		n=strlen(s);
		cerr << n << endl;
		printf("%c\n",sam.issub(s,n)?'Y':'N');
	}
	return 0;
}
