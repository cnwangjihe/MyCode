#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

using namespace std;

int iIn1,iIn2,iIn3,iIn4;

int main()
{
	scanf("%d%d%d%d",&iIn1,&iIn2,&iIn3,&iIn4);
	printf("%d\n",((iIn1^iIn2) & (iIn3 | iIn4)) ^ ((iIn2&iIn3) | (iIn1^iIn4)));
	return 0;
}