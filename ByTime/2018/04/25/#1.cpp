#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

int n,len;

int main()
{
	scanf("%d%d",&n,&len);
	printf("%.5lf\n",20.0*(n*1.0*(len*n+1.0*n*len)));
}
