#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

int n,m,k;

int main()
{
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	printf("%d\n",k*2);
	return 0;
}