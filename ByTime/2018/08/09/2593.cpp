#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1509;

struct Tnode
{
	int x,y;
	Tnode(){}
	Tnode(int a,int b):x(a),y(b){}
	Tnode operator-(const Tnode &a){return Tnode(this->x-a.x,this->y-a.y);}
	int operator*(const Tnode &a){return this->x*a.y-this->y*a.x;}
};

Tnode a[MAXN];
double sum;
int cnt;
int n;

int main()
{
	freopen("2593.in","r",stdin);
	freopen("2593.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		sum=0;
		scanf("%d",&n);
		if (n<3)
		{
			printf("0.000000\n");
			continue;
		}
		cnt=0;
		for (int i=0;i<n;i++)
			scanf("%d%d",&a[i].x,&a[i].y);
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				for (int k=j+1;k<n;k++)
					sum+=abs((a[j]-a[i])*(a[k]-a[i])),cnt++;
	//	cerr << cnt << ' ' << sum << ' ' << 1/((n*1.0/3)/n/(n-1.0)/(n-2.0)) << endl;
		printf("%.6lf\n",(double)sum*3*(n/3)/n/(n-1)/(n-2));
	}
	return 0;
}
