#include <bits/stdc++.h>

using namespace std;

struct Twall{double x,y[4];};

const int MAXN = 22;
const double DINF = 2147483647;

Twall w[MAXN];
double dis[MAXN][4];
int n;

bool through(int l,int r,int c1,int c2)
{
	if (l==r || l+1==r)
		return 1;
	double x1=w[l].x,x2=w[r].x,y1=w[l].y[c1],y2=w[r].y[c2];
	double k=(y1-y2)/(x1-x2),b=y1-x1*k,y;
	for (int i=l+1;i<r;i++)
	{
		y=k*w[i].x+b;
		if ((y<w[i].y[0] || y>w[i].y[1]) && (y<w[i].y[2] || y>w[i].y[3]))
			return 0;
	}
	return 1;
}

double calc(int l,int r,int c1,int c2)
{
	return sqrt((w[l].x-w[r].x)*(w[l].x-w[r].x)+(w[l].y[c1]-w[r].y[c2])*(w[l].y[c1]-w[r].y[c2]));
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lf",&w[i].x);
		for (int j=0;j<4;j++)
			scanf("%lf",&w[i].y[j]);
	}
	w[0].x=0;
	w[0].y[0]=w[0].y[1]=w[0].y[2]=w[0].y[3]=5;
	w[n+1].x=10;
	w[n+1].y[0]=w[n+1].y[1]=w[n+1].y[2]=w[n+1].y[3]=5;
	dis[0][0]=dis[0][1]=dis[0][2]=dis[0][3]=0;
	for (int i=1;i<=n+1;i++)
	{
		for (int ii=0;ii<4;ii++)
		{
			dis[i][ii]=DINF;
			for (int j=0;j<i;j++)
			{
				for (int jj=0;jj<4;jj++)
				{
					if (!through(j,i,jj,ii))
						continue;
				//	if (dis[i][ii]>dis[j][jj]+calc(j,i,jj,ii))
				//		cerr << i << ',' << ii << "  " << j << ',' << jj << endl;
					dis[i][ii]=min(dis[i][ii],dis[j][jj]+calc(j,i,jj,ii));
				}
			}
		}
	}
	printf("%.2f\n",min(dis[n+1][0],min(dis[n+1][1],min(dis[n+1][2],dis[n+1][3]))));
	return 0;
}