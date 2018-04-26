#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 10006;

struct Tnode{
	bool v;
	int connect[11];
}node[MAXN*10];

char s[12];
int n,m,fp;

void _insert(char s[])
{
	int slen=strlen(s),root=0;
	for (int i=0;i<slen;i++)
	{
		if (node[root].connect[int(s[i])-'0']!=0) root=node[root].connect[int(s[i])-'0'];
		else root=node[root].connect[int(s[i])-'0']=++fp;
	}
	node[root].v=1;
	return ;
}

bool _ask(char s[])
{
	int slen=strlen(s),root=0;
	for (int i=0;i<slen;i++)
	{
		if (node[root].connect[int(s[i])-'0']!=0) root=node[root].connect[int(s[i])-'0'];
		else return false;
	}
	if (node[root].v==1) return true;
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(node,0,sizeof node);
	fp=0;
	for (int i=0;i<n;i++) 
	{
		scanf("%s",s);
		_insert(s);
	}
	for (int i=0;i<m;i++)
	{
		scanf("%s",s);
		if (_ask(s)) printf("YES\n");
			else printf("NO\n");
	}
	return 0;
}