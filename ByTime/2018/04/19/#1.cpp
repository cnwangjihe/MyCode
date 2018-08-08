#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#define mmst(a, b) memset(a, b, sizeof(a))
#define mmcp(a, b) memcpy(a, b, sizeof(b))

typedef long long LL;

const int N=1200000,oo=1e9+7;

struct yy
{
	int x,y;
}f[N];

bool operator <(yy a,yy b)
{
	if(a.x==b.x)
	return a.y>b.y;
	return a.x<b.x;
}

void Getmin(yy &a,yy b)
{
	if(b<a)
	a=b;
}

int S,n,a[22],nn;

int main()
{
	freopen("bag.in","r",stdin);
	freopen("#1.out","w",stdout);
	
	cin>>n>>S;
	
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	
	for(int i=1;i<N;i++)
	f[i].x=oo;
	
	nn=(1<<n)-1;
	
	for(int i=0;i<nn;i++)
	for(int j=1;j<=n;j++)
	if(!(i&(1<<(j-1))))
	if(f[i].y>=a[j])
	{
		yy hy;
		hy.x=f[i].x;
		hy.y=f[i].y-a[j];
		Getmin(f[i|(1<<(j-1))],hy);
	}
	else
	{
		yy hy;
		hy.x=f[i].x+1;
		hy.y=S-a[j];
		Getmin(f[i|(1<<(j-1))],hy);
	}
	
	cout<<f[nn].x<<endl;
	
    return 0;
}

