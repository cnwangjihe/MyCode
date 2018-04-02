#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

struct Tnode {int x,y,i;};

const int MAXN = 1000009;

Tnode node[MAXN];
int D,U,LD,LU,RD,RU;
int n,ttt;
bool f1,f2,f3,f4,f5,f6,f7,f8; 

int main()
{
	freopen("lighthouse.in","r",stdin);
	freopen("lighthouse.out","w",stdout);
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		U=D=LD=LU=RU=RD=1;
		f1=f2=f3=f4=f5=f6=f7=f8=1;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&node[i].x,&node[i].y);
			if (i==1)
				continue;
			
			if (node[LD].x>node[i].x)
				LD=LU=i,f5=1;
			else
				if (node[LD].x==node[i].x && node[LD].y!=node[i].y)
				{
					f5=0;
					if (node[LD].y>node[i].y)
						LD=i;
					if (node[LU].y<node[i].y)
						LU=i;
				}
			
			if (node[RD].x<node[i].x)
				RD=RU=i,f6=1;
			else
				if (node[RD].x==node[i].x && node[RD].y!=node[i].y)
				{
					f6=0;
					if (node[RD].y>node[i].y)
						RD=i;
					if (node[RU].y<node[i].y)
						RU=i;
				}
			if (node[U].y<node[i].y)
				U=i,f7=1;
			else
				if (node[U].y==node[i].y && node[U].x!=node[i].x)
					f7=0;
			
			if (node[D].y>node[i].y)
				D=i,f8=1;
			else
				if (node[D].y==node[i].y && node[D].x!=node[i].x)
					f8=0;
			
		}
		for (int i=1;i<=n;i++)
		{
			if (node[i].y<node[LD].y)
				f1=0;
			if (node[i].y>node[LU].y)
				f2=0;
			if (node[i].y<node[RD].y)
				f3=0;
			if (node[i].y>node[RU].y)
				f4=0;
		}
	//	cerr << LD << ' ' << LU << ' ' << RD << ' ' << RU << '\n';
		if (f1|f2|f3|f4)
		{
			printf("Yes\n");
			continue;
		}
		int k;
		for (int i=1;i<=n;i++)
		{
			k=node[U].y-node[i].y;
			f7&=(abs(node[i].x-node[U].x)<=k);
			k=node[i].y-node[D].y;
			f8&=(abs(node[i].x-node[D].x)<=k);
			k=node[i].x-node[LD].x;
			f5&=(abs(node[i].y-node[LD].y)<=k);
			k=node[RD].x-node[i].x;
			f6&=(abs(node[i].y-node[RD].y)<=k);
		}
		if (f5|f6|f7|f8)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
