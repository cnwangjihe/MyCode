#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode
{
	int x,y;
}a[100005];

struct Tower
{
	int x,y,i,v;
}b[100005];

int n,m;
long long ans=1000000000000000009ll;
int cost;

bool _cmp1(Tnode a,Tnode b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
bool _cmp2(Tower a,Tower b) {return a.x==b.x?a.y<b.y:a.x<b.x;}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a,a+n,_cmp1);
	for (int i=0;i<m;i++) 
		scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].v),b[i].i=i;
	sort(b,b+m,_cmp2);
	for (int i=0;i<m;i++)
	{
		cost=0;
		for (int j=0;j<n;j++)
			cost=max(cost,abs(a[j].x-b[i].x)+abs(a[j].y-b[i].y));
		ans=min(ans,(long long)cost*(long long)b[i].v);
	}
	printf("%d\n",ans);
	return 0;
}
