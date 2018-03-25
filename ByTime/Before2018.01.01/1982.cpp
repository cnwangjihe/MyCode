#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

struct data
{int l,r,v;};
data a[1000005];
int n,x,mi,qs[1000005],js[1000005],p,mm;
bool cmp(data a,data b)
{
	if (a.r-a.l!=b.r-b.l)return a.r-a.l<b.r-b.l;
	else return a.l<b.l;
}
int main()
{
	freopen("1982.in","r",stdin);
	freopen("1982.out","w",stdout);
	cin>>n>>x;
	mi=2000000007;
	for (int i=1;i<=n;i++)
	{
        scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].v);
    }
    sort(a+1,a+1+n,cmp);
    qs[a[1].r-a[1].l+1]=1;
    for (int i=2;i<=n;i++)
    {
    	if (a[i].r-a[i].l!=a[i-1].r-a[i-1].l)
    	{
    		js[a[i-1].r-a[i-1].l+1]=i-1;
    		qs[a[i].r-a[i].l+1]=i;
    	}
    }
    js[a[n].r-a[n].l+1]=n;
    for (int i=0;i<=x;i++)
    {
    	if (qs[i]!=0 && qs[x-i]!=0)
    	{
    		p=qs[x-i]-1;mm=1000000007;
    		for (int j=qs[i];j<=js[i];j++)
    		{
    			while (a[p+1].r<a[j].l && p<js[x-i])
    			{
    				p++;mm=min(mm,a[p].v);
    		    }
    		    if (mm!=1000000007)mi=min(mi,mm+a[j].v);
    		}
    	}
    }
    if (mi!=2000000007)cout<<mi;
    else printf("-1");return 0;
}
