#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

using namespace std;

const double eps = 10e-7;

struct Tdata {double x,y;};
Tdata a[15];
int n,L,R;

double getdis(double x1,double y1,double x2,double y2) {return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

bool check(double x,double y)
{
	bool flag=0;
	double tmp;
	for (int i=1;i<=n;i++)
	{
		tmp=getdis(x,y,a[i].x,a[i].y);
		if(tmp<R+eps)
		{
			flag=1;
			break;
		}
	}
	if(!flag)
		return printf("%0.6lf %0.6lf\n",x,y),1;
	return 0;
}

double getrand()
{
	double x=rand()%(L*1000);x=x*1.0/1000;
	return x;
}

int main()
{
	double x,y;
	scanf("%d%d",&n,&L);
	R=(double)L/(double)n;
	srand((n%1273)*L);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lf%lf",&x,&y);
		a[i].x=x;a[i].y=y;
	}

	if(n==1)
	{
		if (check(0,L))
			return 0;
		if (check(L,L))
			return 0;
		if (check(0,0))
			return 0;
		if (check(L,0))
			return 0;
		printf("GG\n");
		return 0;
	}
	while (!check(getrand(),getrand()));
	return 0;
}