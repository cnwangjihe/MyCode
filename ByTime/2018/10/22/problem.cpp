#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {-1,1,0,0},
		  dy[4] = {0,0,-1,1};

const int MAXN = 109,
		  MAXK = 1009;

int n,m,k;

struct Tnode
{
	int x,y,d,v,died;
	inline void turn()
	{
		d=(d/2*2)+(d%2+1)%2;
		return ;
	}
	inline bool wall(){return (x+dx[d])==n+1 || (y+dy[d])==m+1 || (x+dx[d])==0 || (y+dy[d])==0;}
	inline void walk()
	{
		if (wall())
			turn();
		else
			x+=dx[d],y+=dy[d];
		return ;
	}
};

Tnode a[MAXK];
int f[MAXN][MAXN];
int t;

int main()
{
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	memset(f,-1,sizeof f);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<k;i++)
		scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].d,&a[i].v);
	scanf("%d",&t);
	int x,y;
	for (int tt=0;tt<t;tt++)
	{
		for (int i=0;i<k;i++)
		{
			if (a[i].died)
				continue;
			a[i].walk();
			x=a[i].x,y=a[i].y;
			if (~f[x][y])
			{
				if (a[f[x][y]].v>a[i].v)
					a[i].died=1;
				else
					a[f[x][y]].died=1,f[x][y]=i;
			}
			else
				f[a[i].x][a[i].y]=i;
		}
		for (int i=0;i<k;i++)
			f[a[i].x][a[i].y]=-1;
	}
	for (int i=0;i<k;i++)
		printf("%d %d\n",a[i].x,a[i].y);
	return 0;
}