#include <bits/stdc++.h>

using namespace std;

#undef RAND_MAX
#define RAND_MAX 2147483640

const int MAXN = 50009;

struct Tnode{int lc,rc,k,v,s;};

struct Treap
{
	Tnode t[4000009];
	int fp=1,d=0;
	int st[MAXN];
	int newnode() {t[fp].k=rand();return fp++;}
	void up(int u) {t[u].s=t[t[u].lc].s+t[t[u].rc].s+1;}
	int merge(int a,int b)
	{
		/*
		int nu=newnode();
		if (!a)
		{
			t[nu]=t[b];
			return nu;
		}
		if (!b)
		{
			t[nu]=t[a];
			return nu;
		}*/
		if (!a)
			return b;
		if (!b)
			return a;
		int nu=newnode();
		if (t[a].k<t[b].k)
		{
			t[nu]=t[a];
			t[nu].rc=merge(t[a].rc,b);
			up(nu);
			return nu;
		}
		else
		{
			t[nu]=t[b];
			t[nu].lc=merge(a,t[b].lc);
			up(nu);
			return nu;
		}
	}
	pair<int,int> split(int u,int k)
	{
		if (!u)
			return make_pair(0,0);
		if (k==0)
			return make_pair(0,u);
		if (k==t[u].s)
			return make_pair(u,0);
		pair<int,int> tmp;
		int nu=newnode();
		t[nu]=t[u];
		if (k<=t[t[u].lc].s)
		{
			tmp=split(t[u].lc,k);
			t[nu].lc=tmp.second;
			tmp.second=nu;
		}
		else
		{
			tmp=split(t[u].rc,k-t[t[u].lc].s-1);
			t[nu].rc=tmp.first;
			tmp.first=nu;
		}
		up(nu);
		return tmp;
	}

	int build(char *s)
	{
		int root = newnode();
		t[root].k=-1;
		st[0] = root;
		int sz = 1;
		for (int i=0;s[i];i++)
		{
			int p = sz - 1;
			int now=newnode();
			t[now].v=(int)s[i];
			while (t[st[p]].k>t[now].k)
				up(st[p--]);
			if (p != sz - 1) 
				t[now].lc=st[p+1]; 
			t[st[p]].rc=now;
			sz=p+1;
			st[sz++]=now;
		}
		while (sz) up(st[--sz]);
		return t[root].rc;
	}
	/*
	int query(int u,int p)
	{
		if (p<=t[t[u].lc].s)
			return query(t[u].lc,p);
		if (p==t[t[u].lc].s+1)
			return u;
		return query(t[u].rc,p-t[t[u].lc].s-1);
	}
	void print(int u,int& c)
	{
		if (!u || !c)
			return ;
		print(t[u].lc,c);
		putchar(t[u].v);
		c--;
		print(t[u].rc,c);
		return ;
	}*/
	void print(int u)
	{
		if (!u)
			return ;	
		print(t[u].lc);
		putchar(t[u].v);
		if (t[u].v==(int)'c')
			d++;
		print(t[u].rc);
		return ;
	}
}Treap;

char s[MAXN];
int root[MAXN];
int m,n=0;
pair<int,int> tmp;

int main()
{
	root[0]=0;
	int type,p,c,v;
	srand(time(0));
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d",&type);
		if (type==1)
		{
			scanf("%d%s",&p,s);
			p-=Treap.d;
			tmp=Treap.split(root[n],p);
			int t=Treap.build(s);
		//	cerr << tmp.first << ' ' << tmp.second << '\n';
			root[++n]=Treap.merge(tmp.first,Treap.merge(t,tmp.second));
		//	Treap.print(root[n]);
		}
		if (type==2)
		{
			scanf("%d%d",&p,&c);
			p-=Treap.d,c-=Treap.d;
			tmp=Treap.split(root[n],p-1);
			tmp.second=Treap.split(tmp.second,c).second;
			root[++n]=Treap.merge(tmp.first,tmp.second);
		}
		if (type==3)
		{
			scanf("%d%d%d",&v,&p,&c);
			v-=Treap.d;p-=Treap.d;c-=Treap.d;
			tmp=Treap.split(root[v],p-1);
			tmp=Treap.split(tmp.second,c);
			Treap.print(tmp.first);
			putchar('\n');
		}
	}
	return 0;
}