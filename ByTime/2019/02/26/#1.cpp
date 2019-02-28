#include <bits/stdc++.h>
using namespace std;

const int mx=1e5+10;

int n,m;
int a[mx];
struct Tq
{
	int sx,sy,tx,ty;
};
Tq q[mx];

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int rmq[20][mx],lg[mx];

void getrmq()
{
	lg[0]=lg[1]=0;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) rmq[0][i]=a[i];
	for(int k=1;k<=17;k++)
		for(int i=1;i+(1<<(k-1))<=n;i++)
			rmq[k][i]=min(rmq[k-1][i],rmq[k-1][i+(1<<(k-1))]);
}

int askrmq(int l,int r)
{
	if(l>r) swap(l,r);
	int k=lg[r-l+1];
	return min(rmq[k][l],rmq[k][r-(1<<k)+1]);
}

int row(int x,int p1,int p2)
{
	return min(min(abs(p1-p2),p2+1),a[x]-p2+1);
}

void task1()
{
	getrmq();
	int tmp=0,tmp2=0;
	for(int i=0;i<m;i++)
	{
		int sx=q[i].sx,sy=q[i].sy,tx=q[i].tx,ty=q[i].ty;
		int ans=1000000000;
		for(int j=1;j<=n;j++)
		{
			tmp=askrmq(tx,j);
			if(tmp<a[j]) continue;
			tmp2=abs(sx-j)+abs(j-tx)+row(j,min(sy,askrmq(sx,j)),a[j])+row(tx,a[j],ty);
			ans=min(ans,tmp2);
		}
		printf("%d\n",ans);
	}
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("#1.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	m=read();
	for(int i=0;i<m;i++)
		q[i].sx=read(),q[i].sy=read(),q[i].tx=read(),q[i].ty=read();
	
	if(n<=2000 && m<=2000) return task1(),0;
	
	
	return 0;
}
