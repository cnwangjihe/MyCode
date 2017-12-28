#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 2010;
const double eps = 0.0000000000001;
const long long M1 = 998244353;
const long long M2 = 1000000007;
const long long M  = 1333331;

struct Hash_Tdata
{
	int vX,vY,id;
}Hash[M];

struct Tdata
{
	double X,Y;
}point[MAXN];
Tdata mid;

double len[MAXN];
bool vis[MAXN];
Tdata temp[MAXN];
int n;

void died()
{
	printf("-1\n");
	exit(0);
}

void reset()
{
	for (int i=0; i<M; i++) Hash[i].vX=M1;
	memset(vis,0,sizeof vis);
	mid.X=mid.Y=0;
}

void Push(long long x,long long y,int Id)
{
	long long v=((x*M1+y*M2)%M+M)%M;
	while (Hash[v].vX!=M1) v=(v+1)%M;
	Hash[v].vX=x
	Hash[v].vY=y;
	Hash[v].id=Id;
}

Hash_Tdata Judge(double x,double y)
{
	Hash_Tdata z;
	z.vX=z.vY=M1;
	double valX=floor(x+eps),valY=floor(y+eps);
	if ( fabs(valX-x)>eps || fabs(valY-y)>eps ) return z;
	z.vX=(int)floor(valX+eps);
	z.vY=(int)floor(valY+eps);
	return z;
}

bool Check(long long x,long long y)
{
	long long v=((x*M1+y*M2)%M+M)%M;
	while ( Hash[v].vX!=M1 && ( Hash[v].vX!=x || Hash[v].vY!=y ) ) v=(v+1)%M;
	if (Hash[v].vX==M1) return false;
	Hash[v].vX=M2;
	vis[ Hash[v].id ]=true;
	return true;
}

double calc(Tdata x,Tdata y,Tdata z)
{
	Tdata a;
	a.X=y.X-x.X;
	a.Y=y.Y-x.Y;
	Tdata b;
	b.X=z.X-x.X;
	b.Y=z.Y-x.Y;
	return ( a.X*b.Y-a.Y*b.X );
}

int main()
{
	int x,y;
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		scanf("%d%d",&x,&y);
		Push(x,y,i);
		point[i].X=(double)x;
		point[i].Y=(double)y;
		mid.X+=x,mid.Y+=y;
	}
	mid.X/=(double)n,mid.Y/=(double)n;

	for (int i=1; i<=n; i++) 
		if (!vis[i])
		{
			double x=mid.X*2-point[i].X;
			double y=mid.Y*2-point[i].Y;
			if ( fabs(x-point[i].X)<=eps && fabs(y-point[i].Y)<=eps )
			{
				vis[i]=1;
				continue;
			}
			Hash_Tdata z=Judge(x,y);
			if ( z.vX!=M1 && Check(z.vX,z.vY) )
				Check( (int)floor(point[i].X+eps) , (int)floor(point[i].Y+eps) );
		}

	int num=0,x=0;
	for (int i=1; i<=n; i++) 
		if (!vis[i]) num++,x=i;
	if (num<=2) 
		died();
	int ans=0;
	for (int y=1; y<=n; y++) 
		if (!vis[y])
		{
			Tdata z;
			z.X=(point[x].X+point[y].X)/2;
			z.Y=(point[x].Y+point[y].Y)/2;
			int now=0;
			for (int k=1; k<=n; k++) if ( !vis[k] && k!=x && k!=y )
				len[++now]=calc(point[k],mid,z);
			sort(len+1,len+now+1);
			bool sol=true;
			for (int i=1; i<=(now+1)/2; i++)
			{
				int j=now-i+1;
				if (fabs(len[i]+len[j])>eps)
				{
					sol=false;
					break;
				}
			}
			if (sol) ans++,temp[ans]=z;
		}
	int sum=ans;
	for (int i=2; i<=sum; i++)
		for (int j=1; j<i; j++)
			if ( fabs( calc(mid,temp[j],temp[i]) )<=eps )
			{
				ans--;
				break;
			}
	printf("%d\n",ans);
	return 0;
}
