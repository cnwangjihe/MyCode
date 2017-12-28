#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

int ttt,n,ans;

int main()
{
	freopen("2366.in","r",stdin);
	freopen("2366.out","w",stdout);
	scanf("%d",&ttt);
	for (int i=0;i<ttt;i++)
	{
		scanf("%d",&n);
		ans=n/4;
		if (n%4==1 || n%4==3) ans--;
		if (n==11) ans=-1;
		printf("%d\n",ans<=0?-1:ans);	
	}
	return 0;
}
