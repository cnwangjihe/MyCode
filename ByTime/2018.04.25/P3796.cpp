#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000009,
		  MAXP = 152*75;

struct Tnode
{
	int Next[26],v,fail,pos[152],tp;
	inline void clean()
	{
		v=0;
		memset(Next,-1,sizeof Next);
		tp=0;
		fail=-1;
		return ;
	}
	Tnode() {clean();}
};

int cnt[156];

struct Tac
{
	Tnode t[MAXP];
	int line[MAXP];
	int fp,root;
	void clean()
	{
		fp=1;root=0;;
		for (int i=0;i<MAXP;i++)
			t[i].clean();
		return ;
	}
	Tac() {clean();}
	int Newnode() {return fp++;}
	void Insert(char *s,int len,int id)
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
		t[u].pos[t[u].tp++]=id;
		return ;
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
			//	cerr << u <<' '<< v << ' ' << t[v].fail <<'\n';
			}
		}
		return ;
	}
	void Query(char *s,int len)
	{
		int u=root,v,c;
		for (int i=0;i<len;i++)
		{
			c=s[i]-'a';
			while ((~u) && (t[u].Next[c]==-1))
				u=t[u].fail;
			if ((~u) && (~t[u].Next[c]))
			{
				u=t[u].Next[c];
				v=u;
				while (~v)
				{
					for (int i=0;i<t[v].tp;i++)
						cnt[t[v].pos[i]]++;
					v=t[v].fail;
				}
			}
			else
				u=root;
		}
	}
};

int n,Max;
Tac AC;
char s[MAXN],c[151][78];

int main()
{
	while (scanf("%d",&n) && n)
	{
		AC.clean();
		Max=0;
		memset(cnt,0,sizeof cnt);
		for (int i=0;i<n;i++)
		{
			scanf("%s",c[i]);
			AC.Insert(c[i],strlen(c[i]),i);
		}
		AC.Build();
		scanf("%s",s);
		AC.Query(s,strlen(s));
		for (int i=0;i<n;i++)
			Max=max(Max,cnt[i]);
		printf("%d\n",Max);
		for (int i=0;i<n;i++)
			if (Max==cnt[i])
				printf("%s\n",c[i]);
	}
	return 0;
}