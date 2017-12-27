#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define maxn 1100000
#define mem(a,b) memset(a,b,sizeof(a))
#define root10 ch[ch[root][1]][0]
#define root1 ch[root][1]
int size[maxn];
int ch[maxn][2];
int pre[maxn];
int root,tot;
int key[maxn];
int val[maxn];
int n;
int pos;
void Treaval(int x) {
	if(x) {
		Treaval(ch[x][0]);
		printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,key = %2d \n",x,ch[x][0],ch[x][1],pre[x],size[x],key[x]);
		Treaval(ch[x][1]);
	}
}
void debug() {printf("root:%d\n",root);Treaval(root);}
//以上Debug
void init()
{
}
void newnode(int &x,int k,int p,int father)
{
	x=++tot;
	pre[x]=father;
	size[x]=1;
	ch[x][0]=ch[x][1]=0;
	key[x]=p;
	val[x]=k;
}
void push_down(int x)
{
}
void push_up(int x)
{
}
void rot(int x,int kind)
{
	int y=pre[x];
	push_down(y);
	push_down(x);
	ch[y][!kind]=ch[x][kind];
	pre[ch[x][kind]]=y;
	if(pre[y])ch[pre[y]][ch[pre[y]][1]==y]=x;
	pre[x]=pre[y];
	ch[x][kind]=y;
	pre[y]=x;
	push_up(y);
	push_up(x);
}
void splay(int x,int goal)
{
	push_down(x);
	while(pre[x]!=goal)
	{
		if(pre[pre[x]]==goal)
		{
			push_down(pre[x]);
			push_down(x);
			rot(x,ch[pre[x]][0]==x);
		}
		else
		{
			int y=pre[x];
			push_down(pre[y]);
			push_down(y);
			push_down(x);
			int kind=ch[pre[y]][0]==y;
			if(ch[y][kind]==x)
			{
				rot(x,!kind);
				rot(x,kind);
			}
			else
			{
				rot(y,kind);
				rot(x,kind);
			}
		}
	}
	push_up(x);
	if(goal==0)root=x;
}

void insert(int k,int p)
{
	int rt=root;
	int r=root;
	while(rt!=0)
	{
		r=rt;
		if(key[rt]<p)rt=ch[rt][1];
		else rt=ch[rt][0];
		//cout<<r<<" "<<rt<<endl;
	}
	newnode(ch[r][key[r]<p],k,p,r);
	splay(ch[r][key[r]<p],root);
	ch[0][0]=ch[0][1]=0;
}

int get_min(int rt)
{
	while(ch[rt][0])rt=ch[rt][0];
	if(rt==root)root=ch[rt][1];
	ch[pre[rt]][0]=ch[rt][1];
	pre[ch[rt][1]]=pre[rt];
	return val[rt];
}
int get_max(int rt)
{
	while(ch[rt][1])rt=ch[rt][1];
	if(rt==root)root=ch[rt][0];
	ch[pre[rt]][1]=ch[rt][0];
	pre[ch[rt][0]]=pre[rt];
	return val[rt];
}
int main()
{
	root=tot=0;
	int op,k,p;
	while(~scanf("%d",&op)&&(op))
	{

		if(op==1)
		{
			scanf("%d%d",&k,&p);
			insert(k,p);
		}
		if(op==2)
		{
			printf("%d\n",get_max(root));
		}
		if(op==3)
		{
			printf("%d\n",get_min(root));
		}
	    debug();
	}
	return 0;
}











