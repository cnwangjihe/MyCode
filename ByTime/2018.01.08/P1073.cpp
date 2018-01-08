#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include<queue>

using namespace std;

const int MAXN = 100009;

struct Tnode {int b,next,v;};

Tnode st[MAXN],nd[MAXN];
int a[MAXN];
bool vis[MAXN];
int minl[MAXN],maxl[MAXN],head1[MAXN],head2[MAXN];
int n,m,fp1,fp2,ans=0;
queue <int> q;

void add(int x,int y,int z)
{
	fp1++;
	st[fp1].b=y;
	st[fp1].v=z;
	st[fp1].next=head1[x];
	head1[x]=fp1;
	return ;
}

void add2(int x,int y,int z)
{
	fp2++;
	nd[fp2].b=y;
	nd[fp2].v=z;
	nd[fp2].next=head2[x];
	head2[x]=fp2;
	return ;
}

void spfa1()
{
	memset(vis,0,sizeof vis);		 
	q.push(1);  
	vis[1]=1;
	while (!q.empty())
	{
		int t=q.front();
		q.pop();
		for (int i=head1[t];i!=0;i=st[i].next)
		{
			int b=st[i].b;	
			if (minl[b]>min(minl[t],st[i].v))
			{
			   minl[b]=min(minl[t],st[i].v);	
			   if (!vis[b])
				   q.push(b),vis[b]=1;
			}
		}
		vis[t]=0;
	}
	return ;
}
void spfa2()
{
	memset(vis,0,sizeof vis);
	q.push(n);
	vis[n]=1;
	while (!q.empty())
	{
		int t=q.front();
		q.pop();
		for (int i=head2[t];i!=0;i=nd[i].next)
		{
			int b=nd[i].b;
			if(maxl[b]<max(maxl[t],nd[i].v))
			{
				maxl[b]=max(maxl[t],nd[i].v);
				if(!vis[b])
					q.push(b),vis[b]=1;
			}
		}
		vis[t]=0;
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		minl[i]=10000,maxl[i]=0;	
	for (int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (z==2)
		{
			add2(x,y,a[y]);
			add(y,x,a[x]);
			add2(y,x,a[x]);
			add(x,y,a[y]);
		}
		else
		{
			add2(y,x,a[x]);
			add(x,y,a[y]);
		}
	}
	spfa1();
	spfa2();
	for (int i=1;i<=n;i++)
		ans=max(ans,maxl[i]-minl[i]);
	printf("%d\n",ans);
	return 0;
}
