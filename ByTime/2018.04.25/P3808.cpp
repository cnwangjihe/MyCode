#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000009;

struct Tnode
{
	int Next[26],v,fail;
	inline void clean()
	{
		v=0;
		memset(Next,-1,sizeof Next);
		fail=-1;
		return ;
	}
	Tnode() {clean();}
};

struct Tac
{
	Tnode t[MAXN];
	int line[MAXN];
	int fp,root;
	Tac() {fp=1;root=0;}
	int Newnode() {return fp++;}
	void Insert(char *s,int len)
	{
		int u=root,v;
		for (int i=0;i<len;i++)
		{
			if (~t[u].Next[s[i]-'a'])
				u=t[u].Next[s[i]-'a'];
			else
			{
				v=Newnode();
				t[u].Next[s[i]-'a']=v;
				u=v;
			}
		}
		t[u].v++;
	}
	void Build()
	{
		int u,v,head=0,tail=0,k;
		line[tail++]=root;
		while (head!=tail)
		{
			u=line[head++];
			for (int i=0;i<26;i++)
			{
				v=t[u].Next[i];
				if (v==-1)
					continue;
				k=t[u].fail;
				while ((~k) && (t[k].Next[i]==-1))
					k=t[k].fail;
				if ((~k) && (~t[k].Next[i]))
					t[v].fail=t[k].Next[i];
				else
					t[v].fail=0;
				line[tail++]=v;
	//			cerr << u <<' '<< v << ' ' << t[v].fail <<'\n';
			}
		}
		return ;
	}
	int Query(char *s,int len)
	{
		int u=root,v,c,ans=0;
		for (int i=0;i<len;i++)
		{
			c=s[i]-'a';
			while ((~u) && (t[u].Next[c]==-1))
				u=t[u].fail;
			if ((~u) && (~t[u].Next[c]))
			{
				u=t[u].Next[c];
				v=u;
				while ((~v) && (~t[v].v))
				{
					ans+=t[v].v;
					t[v].v=-1;
					v=t[v].fail;
				}
			}
			else
				u=root;
		}
		return ans;
	}
};

int n;
Tac AC;
char s[MAXN];

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%s",s);
		AC.Insert(s,strlen(s));
	}
	AC.Build();
	scanf("%s",s);
	printf("%d\n",AC.Query(s,strlen(s)));
	return 0;
}