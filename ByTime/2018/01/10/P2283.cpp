/*
a*b>0 b 
*/

/*半平面相交（直线切割多边形）（点标号从1开始）*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 1600;
const double EPS = 1e-10;

struct Point
{
	double x,y;
	Point(){}
	Point(double a,double b)
	{
		x=a,y=b;
	}
};

int cross(Point a,Point b) {return a.x*b.y-a.y*b.x;}
bool _cmp(Point a,Point b) {return cross(a,b)>0;}

Point points[MAXN],p[MAXN],q[MAXN];
int n;
double r;
int cCnt,curCnt;

inline void getline(Point x,Point y,double &a,double &b,double &c){
	a = y.y - x.y;
	b = x.x - y.x;
	c = y.x * x.y - x.x * y.y;
}
inline void initial(){
	for(int i = 1; i <= n; ++i) p[i] = points[i];
	p[n+1] = p[1];
	p[0] = p[n];
	cCnt = n;
}
inline Point intersect(Point x,Point y,double a,double b,double c){
	double u = fabs(a * x.x + b * x.y + c);
	double v = fabs(a * y.x + b * y.y + c);
	return Point( (x.x * v + y.x * u) / (u + v) , (x.y * v + y.y * u) / (u + v) );
}
inline void cut(double a,double b ,double c){
	curCnt = 0;
	for(int i = 1; i <= cCnt; ++i){
		if(a*p[i].x + b*p[i].y + c >= EPS)q[++curCnt] = p[i];
		else {
			if(a*p[i-1].x + b*p[i-1].y + c > EPS){
				q[++curCnt] = intersect(p[i],p[i-1],a,b,c);
			}
			if(a*p[i+1].x + b*p[i+1].y + c > EPS){
				q[++curCnt] = intersect(p[i],p[i+1],a,b,c);
			}
		}
	}
	for(int i = 1; i <= curCnt; ++i)p[i] = q[i];
	p[curCnt+1] = q[1];p[0] = p[curCnt];
	cCnt = curCnt;
}
inline void solve(){
	//注意：默认点是顺时针，如果题目不是顺时针，规整化方向
	initial();
	for(int i = 1; i <= n; ++i){
		double a,b,c;
		getline(points[i],points[i+1],a,b,c);
		cut(a,b,c);
	}
	/*
	如果要向内推进r，用该部分代替上个函数
	for(int i = 1; i <= n; ++i){
		Point ta, tb, tt;
		tt.x = points[i+1].y - points[i].y;
		tt.y = points[i].x - points[i+1].x;
		double k = r / sqrt(tt.x * tt.x + tt.y * tt.y);
		tt.x = tt.x * k;
		tt.y = tt.y * k;
		ta.x = points[i].x + tt.x;
		ta.y = points[i].y + tt.y;
		tb.x = points[i+1].x + tt.x;
		tb.y = points[i+1].y + tt.y;
		double a,b,c;
		getline(ta,tb,a,b,c);
		cut(a,b,c);
	}
	*/
	//多边形核的面积
	double area = 0;
	for(int i = 1; i <= curCnt; ++i)
		area += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
	area = fabs(area / 2.0);
	printf("%lf\n",area);
	//此时cCnt为最终切割得到的多边形的顶点数，p为存放顶点的数组
}
inline void GuiZhengHua(){
	 //规整化方向，逆时针变顺时针，顺时针变逆时针
	for(int i = 1; i < (n+1)/2; i ++)
	  swap(points[i], points[n-i]);//头文件加iostream
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lf%lf",&points[i].x,&points[i].y);
	sort(points+1,points+n+1,_cmp);
	points[n+1] = points[1];
	solve();
}
