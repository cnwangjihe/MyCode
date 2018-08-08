#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct Tnode{int x,y;};

Tnode a[1000009];
int n,tim=0,ans=0;

bool _cmp(Tnode a,Tnode b){return a.y<b.y;}

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a,a+n,_cmp);
	for (int i=0;i<n;i++)
	{
		if (tim<=a[i].x)
			tim=a[i].y,ans++;
	}
	printf("%d\n",ans);
	return 0;
}