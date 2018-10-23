#include <bits/stdc++.h>
using namespace std;

const int mx=1005;
int n,m,k;
struct Tnode
{
	int x,y,d,f;
	int dead;
	Tnode()
	{ dead=0; }
};
Tnode a[mx];
int c[105][105];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int t;


inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int rubx[mx],ruby[mx],top=0;

void clear()
{
	while(top>0) c[rubx[--top]][ruby[top]]=0;
}

int main()
{
	freopen("problem.in","r",stdin);
	freopen("#1.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;i++)
		a[i].x=read(),a[i].y=read(),a[i].d=read(),a[i].f=read();
	t=read();
	
	for(int i=0;i<t;i++)
	{
		clear();
		for(int j=1;j<=k;j++)
		{
			if(a[j].dead) continue;
			int nx=a[j].x,ny=a[j].y;
			if(nx+dx[a[j].d]<1 || nx+dx[a[j].d]>n || ny+dy[a[j].d]<1 || ny+dy[a[j].d]>m) a[j].d^=1;
			else nx=a[j].x+dx[a[j].d],ny=a[j].y+dy[a[j].d];
			a[j].x=nx,a[j].y=ny;
			if(a[c[nx][ny]].f>a[j].f) a[j].dead=1;
			else a[c[nx][ny]].dead=1,c[nx][ny]=j;
			rubx[top]=nx,ruby[top++]=ny;
		}
/*		for(int x=1;x<=n;x++,cerr<<endl)
			for(int y=1;y<=m;y++) cerr<<c[x][y];
		for(int j=1;j<=k;j++)
			cerr<<a[j].x<<" "<<a[j].y<<" "<<a[j].d<<" "<<a[j].f<<" "<<a[j].dead<<endl;
		
		cerr<<endl;
*/	}
	
	for(int i=1;i<=k;i++)
		printf("%d %d\n",a[i].x,a[i].y);
	
	
	return 0;
} 
