#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const bool NEED_PREPARE = 0;

long long sx,sy,sz,ex,ey,ez,tmp;
int k,ans=0;

void _search(long long x,long long y,long long z,int t)
{
	if (t==k)
	{
		if (x+y+z-ex-ey-ez==0 && ((x==ex && y==ey) || (x==ey && y==ex)))
			ans++;
		return ;
	}
	if (x+y+z-ex-ey-ez==0 && ((x==ex && y==ey) || (x==ey && y==ex)) && ((k-t)%2))
		return ;
	if (z<min(x,2*y-x) || z>max(x,2*y-x))
		_search(2*y-x,y,z,t+1);
	if (z<min(y,2*x-y) || z>max(y,2*x-y))
		_search(x,2*x-y,z,t+1);
	if (y<min(x,2*z-x) || y>max(x,2*z-x))
		_search(2*z-x,y,z,t+1);
	if (y<min(z,2*x-z) || y>max(z,2*x-z))
		_search(x,y,2*x-z,t+1);
	if (x<min(y,2*z-y) || x>max(y,2*z-y))
		_search(x,2*z-y,z,t+1);
	if (x<min(z,2*y-z) || x>max(z,2*y-z))
		_search(x,y,2*y-z,t+1);
	return ;
}

long long gcd(int a,int b)
{
	if (!a) return b;
	if (!b) return a;
	return (a%b)?gcd(b,a%b):b;
}

int main()
{
	freopen("rabbits.in","r",stdin);
	freopen("rabbits.out","w",stdout);
	scanf("%I64d%I64d%I64d",&sx,&sy,&sz);
	scanf("%I64d%I64d%I64d",&ex,&ey,&ez);
	scanf("%d",&k);
	if (NEED_PREPARE)
	{
		sy-=sx;sz-=sx;
		ex-=sx;ey-=sx;ez-=sx;
		sx=0;
		if (ex<0)
		{
			sx-=ex;sy-=ex;sz-=ex;
			ey-=ex;ez-=ex;
			ex=0;
		}
		tmp=gcd(sx,gcd(sy,gcd(sz,gcd(ex,gcd(ey,ez)))));
		sx/=tmp;sy/=tmp;sz/=tmp;
		ex/=tmp;ey/=tmp;ez/=tmp;
	}
	if ((sx!=ex || sy!=ey || sz!=ez) && k>13)
		return printf("0\n")&0;
	_search(sx,sy,sz,0);
	printf("%d\n",ans);
	return 0;
}
