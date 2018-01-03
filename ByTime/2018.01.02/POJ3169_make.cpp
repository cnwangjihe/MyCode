#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int MAXN = 5,
		  MAXM = 10;
		  
int n,ml,md,x,y,z;

ofstream fout("POJ3169.in");

int main()
{
	srand(time(0));
	n=rand()%(MAXN-4)+4;
	ml=rand()%MAXM+1;
	md=rand()%MAXM+1;
	
	fout << n << ' ' << ml << ' ' << md << endl;
	for (int i=0;i<ml;i++)
	{
		do
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}
		while (x==y);
		fout << x << ' ' << y << ' ' << rand()%10+1 << '\n';
	}
	for (int i=0;i<md;i++)
	{
		do
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}
		while (x==y);
		fout << x << ' ' << y << ' ' << rand()%10+1 << '\n';
	}
	return 0;
}
