#include <bits/stdc++.h>

using namespace std;

#undef RAND_MAX
#define RAND_MAX 1000009

const int MAXN = 500009;

struct Tnode{int v,k,c[2],s;};

struct Treap
{
	Tnode t[MAXN*50];
	int fp=1;
	int newnode(){t[fp].k=rand();return fp++;}
	void up(int u){t[u].s=t[t[u].c[0]].s+t[t[u].c[1]].s+1;}
	int merge(int a,int b)
	{
		if (!a || !b)
			return a+b;
		int nu=newnode();
		if (t[a].k<t[b].k)
		{
			t[nu]=t[a];
			t[nu].c[1]=merge(t[a].c[1],b);
		}
		else
		{
			t[nu]=t[b];
			t[nu].c[0]=merge(a,t[b].c[0]);
		}
		up(nu);
		return nu;
	}
	pair<int,int> split(int u,int k)
	{
		if (!u)
			return make_pair(0,0);
		int nu=newnode();
		pair<int,int> tmp;
		t[nu]=t[u];
		if (k<t[u].v)
		{
			tmp=split(t[u].c[0],k);
			t[nu].c[0]=tmp.second;
			tmp.second=nu;
		}
		else
		{
			tmp=split(t[u].c[1],k);
			t[nu].c[1]=tmp.first;
			tmp.first=nu;
		}
		up(nu);
		return tmp;
	}
	int getval(int u,bool k){return (!t[u].c[k])?t[u].v:getval(t[u].c[k],k);}
	int getkthval(int u,int k)
	{
		if (t[t[u].c[0]].s+1==k)
			return t[u].v;
		if (k<=t[t[u].c[0]].s)
			return getkthval(t[u].c[0],k);
		else
			return getkthval(t[u].c[1],k-t[t[u].c[0]].s-1);
	}
	void print(int u)
	{
		if (!u)
			return ;	
		print(t[u].c[0]);
		printf("%d ",t[u].v);
		print(t[u].c[1]);
		return ;
	}
}Treap;

int root[MAXN];
int n=0,m;

int main()
{
	int v,t,x,nu;
	pair<int,int> tmp1,tmp2;
	root[0]=0;
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&v,&t,&x);
		if (t==1)
		{
			tmp1=Treap.split(root[v],x);
			nu=Treap.newnode();
		//	Treap.print(tmp1.first);
		//	putchar('\n');
			Treap.t[nu].v=x;
			Treap.t[nu].s=1;
			root[++n]=Treap.merge(Treap.merge(tmp1.first,nu),tmp1.second);
		}
		if (t==2)
		{
			tmp1=Treap.split(root[v],x);
			tmp2=Treap.split(tmp1.first,x-1);
			tmp2.second=Treap.merge(Treap.t[tmp2.second].c[0],Treap.t[tmp2.second].c[1]);
			root[++n]=Treap.merge(tmp2.first,Treap.merge(tmp2.second,tmp1.second));
		}
		if (t==3)
		{
			tmp1=Treap.split(root[v],x-1);
			root[++n]=root[v];
			printf("%d\n",Treap.t[tmp1.first].s+1);
		}
		if (t==4)
		{
			root[++n]=root[v];
			printf("%d\n",Treap.getkthval(root[v],x));
		}
		if (t==5)
		{
			tmp1=Treap.split(root[v],x-1);
			root[++n]=root[v];
			printf("%d\n",Treap.getval(tmp1.first,1));
		}
		if (t==6)
		{
			tmp1=Treap.split(root[v],x);
			root[++n]=root[v];
			printf("%d\n",Treap.getval(tmp1.second,0));
		}
	}
	return 0;
}