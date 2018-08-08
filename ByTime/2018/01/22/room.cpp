#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 109;

struct Tnode{int x,y;};

double f[MAXN];
double ans=1000000000;
Tnode node[MAXN],s;
int n;

int p2(int a) {return a*a;}
double Dis(Tnode a,Tnode b) {return sqrt((double)(p2(a.x-b.x)+p2(a.y-b.y)));}

int main()
{
	freopen("room.in","r",stdin);
	freopen("room.out","w",stdout);
	int now,t1,t2;
	scanf("%d%d%d",&n,&s.x,&s.y);
	for (int i=0;i<n;i++)
		scanf("%d%d",&node[i].x,&node[i].y);
	for (int i=0;i<n;i++)
	{
		f[i]=Dis(s,node[i]);
		f[i+1]=f[i]+Dis(node[i+1],node[i]);
		for (int j=2;j<n;j++)
		{
			now=(i+j)%n;
			t1=(now-1+n)%n;
			t2=(t1+n-1)%n;
			f[now]=min(f[t1]+Dis(node[t1],node[now]),f[t2]+Dis(node[t2],node[now]));
		}
		ans=min(ans,f[(i+n-1)%n]+Dis(node[(i+n-1)%n],s));
		ans=min(ans,f[(i+n-2)%n]+Dis(node[(i+n-2)%n],s));
	}
	printf("%.2f\n",ans);
	return 0;
}
