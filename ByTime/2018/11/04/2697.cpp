#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  INF  = 1000000009;

struct Tnode{int sum,dec;};

Tnode t[MAXN*4];
int a[MAXN],b[MAXN];
int ans=0;
int n,k;

void Down(int u)
{
	if (t[u].dec>t[u*2+1].sum)
	{
		t[u].dec-=t[u*2+1].sum;
		t[u*2+1].dec+=t[u*2+1].sum;
		t[u*2+1].sum=0;
		t[u*2].sum-=t[u].dec;
		t[u*2].dec+=t[u].dec;
	}
	else
	{
		t[u*2+1].sum-=t[u].dec;
		t[u*2+1].dec+=t[u].dec;
	}
	t[u].dec=0;
	return ;
}

void Build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].sum=b[l];
		t[u].dec=0;
		return ;
	}
	int mid=(l+r)/2;
	Build(u*2,l,mid);
	Build(u*2+1,mid+1,r);
	t[u].sum=t[u*2].sum+t[u*2+1].sum;
	return ;
}

int Modify(int u,int l,int r,int ar,int v)
{
	if (ar>=r)
	{
		if (v>t[u].sum)
		{
			t[u].dec+=t[u].sum;
			v-=t[u].sum;
			t[u].sum=0;
			return v;
		}
		t[u].dec+=v;
		t[u].sum-=v;
		return 0;
	}
	Down(u);
	int mid=(l+r)/2,tmp;
	if (ar>mid)
	{
		tmp=Modify(u*2+1,mid+1,r,ar,v);
		if (tmp)
			tmp=Modify(u*2,l,mid,ar,tmp);
	}
	else
		tmp=Modify(u*2,l,mid,ar,v);
	t[u].sum=t[u*2].sum+t[u*2+1].sum;
	return tmp;
}

int Query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u].sum;
	Down(u);
	int mid=(l+r)/2,sum=0;
	if (al<=mid)
		sum+=Query(u*2,l,mid,al,ar);
	if (ar>mid)
		sum+=Query(u*2+1,mid+1,r,al,ar);
	return sum;
}

int main()
{
	freopen("2697.in","r",stdin);
	freopen("2697.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=1;i<n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	b[n]=a[n]=INF;
	for (int i=1;i<=k;i++)
		ans+=a[i],b[i]=0;
	Build(1,1,n);
	int t,v;
	for (int i=1;i<n;i++)
	{
		v=a[i]-Query(1,1,n,i,i);
		t=min(v,Query(1,1,n,i+1,i+k));
	//	cerr << "## " << i << " : " << v << " , " << t << endl;
		ans-=v-t;
		Modify(1,1,n,i+k,t);
	}
	printf("%d\n",ans);
	return 0;
}