#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXQ = 200009;

bool comd;
int n;

struct Tnode
{
	int Max[2],Min[2],Mid[2],Val,lc,rc;
	int Sum;
	Tnode() {Sum=0;lc=rc=-1;}
	int &operator[](int d) {return Mid[d];}
	friend bool operator<(Tnode a,Tnode b) {return a[comd]<b[comd];}
	friend bool operator==(Tnode a,Tnode b) {return a[0]==b[0] && a[1]==b[1];}
};

bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2;}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {return x1>X2||x2<X1||y1>Y2||y2<Y1;}

struct KDtree
{
	int fp,root;
	Tnode t[MAXQ];
	Tnode p[MAXQ];
	KDtree() {fp=0;root=-1;}
	void Up(int u)
	{
		int lc=t[u].lc,rc=t[u].rc;
		t[u].Sum=t[u].Val;
		for (int i=0;i<2;i++)
		{
			t[u].Max[i]=t[u].Min[i]=t[u][i];
			if (~lc)
				t[u].Max[i]=max(t[u].Max[i],t[lc].Max[i]),
				t[u].Min[i]=min(t[u].Min[i],t[lc].Min[i]);
			if (~rc)
				t[u].Max[i]=max(t[u].Max[i],t[rc].Max[i]),
				t[u].Min[i]=min(t[u].Min[i],t[rc].Min[i]);
		}
		if (~lc)
			t[u].Sum+=t[lc].Sum;
		if (~rc)
			t[u].Sum+=t[rc].Sum;
		return ;
	}
	void Rebuild()
	{
		for (int i=0;i<fp;i++)
			p[i]=t[i];
		root=Build(0,fp-1,0);
		return ;
	}
	int Build(int l,int r,int d)
	{
		if (l>r)
			return -1;
		int u=(l+r)/2;
		comd=d;
		nth_element(p+l,p+u,p+r+1);
		t[u]=p[u];
		t[u].lc=Build(l,u-1,d^1);
		t[u].rc=Build(u+1,r,d^1);
		Up(u);
		return u;
	}
	void Insert(int& u,int d,Tnode ins)
	{
		comd=d;
		if (u==-1)
		{
			u=fp++;
			t[u]=ins;
			Up(u);
			return ;
		}
		if (ins==t[u])
		{
			t[u].Val+=ins.Val,t[u].Sum+=ins.Val;
			return ;
		}
		if (ins<t[u])
			Insert(t[u].lc,d^1,ins);
		else
			Insert(t[u].rc,d^1,ins);
		Up(u);
		return ;
	}
	int Query(int u,int x1,int y1,int x2,int y2)
	{
		if (u==-1 || out(x1,y1,x2,y2,t[u].Min[0],t[u].Min[1],t[u].Max[0],t[u].Max[1]))
			return 0;
		if (in(x1,y1,x2,y2,t[u].Min[0],t[u].Min[1],t[u].Max[0],t[u].Max[1]))
			return t[u].Sum;
		int sum=0;
		if (in(x1,y1,x2,y2,t[u][0],t[u][1],t[u][0],t[u][1]))
			sum+=t[u].Val;
		sum+=Query(t[u].lc,x1,y1,x2,y2)+Query(t[u].rc,x1,y1,x2,y2);
		return sum;
	}
}kd;

int main()
{
	int t,x,y,z,x1,x2,y1,y2,cnt=0,ans=0;
	Tnode a;
	scanf("%d",&n);
	while (scanf("%d",&t) && t!=3)
	{
		if (t==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			x^=ans,y^=ans,z^=ans;
			a[0]=x;a[1]=y;a.Val=z;
			kd.Insert(kd.root,0,a);
			cnt++;
			if (cnt%10000==0)
				kd.Rebuild();
		}
		else
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1^=ans,x2^=ans,y1^=ans,y2^=ans;
			ans=kd.Query(kd.root,x1,y1,x2,y2);
			printf("%d\n",ans);
		}
	}
	return 0;
}