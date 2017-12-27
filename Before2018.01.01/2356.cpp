#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

int _x1,_y1,_x2,_y2;
int ans=0;

int main() 
{
	freopen("2356.in","r",stdin);
	freopen("2356.out","w",stdout);
	scanf("%d%d",&_x1,&_y1);
	scanf("%d%d",&_x2,&_y2);
	ans=(abs(_x1-_x2)+abs(_y1-_y2)+2)*2;
	if(!(_x1-_x2) || !(_y1-_y2)) ans+=2;
	printf("%d\n",ans);
	return 0;
}
