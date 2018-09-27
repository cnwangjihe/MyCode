#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn=100005;
struct data
{int v,i;};
data line[maxn],other[maxn];
int n,m,ans,T,p,pp,id,x,las,qs[maxn],js[maxn],pan[maxn],a[maxn];
int p1,p2,xian,add;
int efid(int id)
{
	int lef=0,rig=p+1,mid;
	while (lef+1<rig)
	{
		mid=(lef+rig)/2;
		if (line[mid].i>=id) rig=mid;
		else lef=mid;
	}
	return rig;
}
int efv(int val)
{
	int lef=0,rig=p+1,mid;
	while (lef+1<rig)
	{
		mid=(lef+rig)/2;
		if (line[mid].v>val) rig=mid;
		else lef=mid;
	}
	return lef;
}
int efot(int val,int ll,int rr)
{
	int lef=ll-1,rig=rr+1,mid;
	while (lef+1<rig)
	{
		mid=(lef+rig)/2;
		if (other[mid].v<=val) lef=mid;
		else rig=mid;
	}
	return lef;
}
int main()
{
//	int st=clock();
	freopen("a.in","r",stdin);
	freopen("#1.out","w",stdout);
	cin>>T;
	for (int o=1;o<=T;o++)
	{
		cin>>n>>m;ans=0;
		p=0;pp=0;line[0].v=-1;
		other[0].v=-1;las=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			a[i]=x;
			if (x>line[p].v) 
			{
				p++;ans++;
				line[p].v=x;
				line[p].i=i;
				if (las>0) 
				js[las]=pp;
				pan[i]=p;
			}
			else if (x>line[p-1].v && x>other[pp].v)
			{
				pp++;
				if (qs[line[p].i]==0)
				{
					las=line[p].i;
					qs[las]=pp;
				}
				other[pp].v=x;
				other[pp].i=i;
			}
		}
		if (las>0) js[las]=pp;
		for (int i=1;i<=m;i++)
		{
			scanf("%d %d",&id,&x);
			if (x>a[id])
			{
				p1=efid(id);
				p2=efv(x);
				if (p1>p2+1) printf("%d\n",ans);
				else printf("%d\n",ans-(p2-p1));
			}
			else if (pan[id]>0)
			{
				if (x>line[pan[id]-1].v){xian=x;add=1;}
				else {xian=line[pan[id]-1].v;add=0;}
				if (qs[id]>0)
				{
					p1=efot(xian,qs[id],js[id]);
					printf("%d\n",ans-1+add+(js[id]-p1));
				}
				else printf("%d\n",ans-1+add);
			}
			else printf("%d\n",ans);
		}
		for (int i=1;i<=n;i++)
		{qs[i]=js[i]=pan[i]=0;}
	}
//	cerr << "time: "<< clock()-st << endl;
	return 0;
}
