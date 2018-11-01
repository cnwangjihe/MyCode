#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Ttask
{
	int x,sy,ey,t,i;
	Ttask(int a=0,int b=0,int c=0,int d=0,int e=0):x(a),sy(b),ey(c),t(d),i(e) {}
	friend bool operator < (const Ttask& a,const Ttask& b) {return a.x==b.x?a.t<b.t:a.x<b.x;}
};

Ttask task[MAXN*4];
long long s1[MAXN],s2[MAXN],s3[MAXN],s4[MAXN];
int sx[MAXN],sy[MAXN],ex[MAXN],ey[MAXN];
int cx[MAXN],cy[MAXN];
int t[MAXN*4];
int n,q,fp=0;

void Add(int u,int l,int r,int p)
{
	if (l==r)
	{
		t[u]++;
		return ;
	}
	int mid=(l+r)>>1;
	if (p<=mid)
		Add(u*2,l,mid,p);
	else
		Add(u*2+1,mid+1,r,p);
	t[u]=t[u*2]+t[u*2+1];
	return ;
}

int Query(int u,int l,int r,int al,int ar)
{
	if (ar<al)
		return 0;
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)>>1,sum=0;
	if (al<=mid)
		sum+=Query(u*2,l,mid,al,ar);
	if (ar>mid)
		sum+=Query(u*2+1,mid+1,r,al,ar);
	return sum;
}

inline void New(int x,int sy,int ey,int t,int i)
{
	task[fp++]=Ttask(x,sy,ey,t,i);
	return ;
}

long long C2(long long x) {return x*(x-1)/2ll;}

int main()
{
	freopen("2691.in","r",stdin); 
	freopen("2691.out","w",stdout); 
	int y;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&y);
		New(i,y,y,1,i);
		cx[i]++,cy[y]++;
	}
	for (int i=1;i<=n;i++)
		cx[i]+=cx[i-1],cy[i]+=cy[i-1];
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d%d",&sx[i],&sy[i],&ex[i],&ey[i]);
		New(sx[i],sy[i],ey[i],0,i);
		New(ex[i],sy[i],ey[i],2,i);
	}
	sort(task,task+fp);
	for (int i=0;i<fp;i++)
	{
		if (task[i].t==1)
			Add(1,1,n,task[i].sy);
		if (task[i].t==0)
		{
			s1[task[i].i]=Query(1,1,n,1,task[i].sy-1);
			s2[task[i].i]=Query(1,1,n,task[i].ey+1,n);
		}
		if (task[i].t==2)
		{
			s3[task[i].i]-=Query(1,1,n,1,task[i].sy-1);
			s4[task[i].i]-=Query(1,1,n,task[i].ey+1,n);
		}
	}
	long long ans;
	for (int i=0;i<q;i++)
	{
		ans=0;
		s3[i]+=Query(1,1,n,1,sy[i]-1);
		s4[i]+=Query(1,1,n,ey[i]+1,n);
		ans=C2(n)-C2(cx[sx[i]-1])-C2(n-cx[ex[i]]);
		ans=ans-C2(cy[sy[i]-1])-C2(n-cy[ey[i]])+C2(s1[i])+C2(s2[i])+C2(s3[i])+C2(s4[i]);
		printf("%lld\n",ans);
	}
	return 0;
}