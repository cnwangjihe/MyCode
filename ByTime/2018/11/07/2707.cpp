#include <bits/stdc++.h>

using namespace std;

const int MAXN = 39,
		  MAXS = (1<<19);

const long long INF = 1000000000000000ll;

struct Tquery
{
	long long b,c;
	int k,t,i;
	Tquery(){k=t=0;}
};

Tquery q[MAXS],nq[MAXS];
int a[MAXN],b[MAXN],c[MAXN];
int col[MAXS];
int t[MAXN*4*4];
int n,k,Mink=100000000,Maxk=-1000000000;
long long ans=0;

void calc(int tot,int m,int tt)
{
	q[tot].b=q[tot].c=0;
	q[tot].k=q[tot].t=0;
	q[tot].i=tot;
	for (int i=1;i<(1<<m);i++)
	{
		for (int j=0;j<m;j++)
		{
			if (i&(1<<j))
			{
				q[tot+i].b=q[tot+(i^(1<<j))].b+(a[tt+j]-b[tt+j]);
				q[tot+i].c=q[tot+(i^(1<<j))].c+(a[tt+j]-c[tt+j]);
				q[tot+i].i=tot+i;
				break;
			}
		}
	}
	for (int i=1;i<(1<<m);i++)
	{
		for (int j=0;j<m;j++)
			if (i&(1<<j))
				q[i+tot].k++;
	}
}

bool _cmp(Tquery a,Tquery b) {return (a.b==b.b)?(a.t<b.t):(a.b<b.b);}

void _add(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u]+=v;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_add(u*2,l,mid,p,v);
	else
		_add(u*2+1,mid+1,r,p,v);
	t[u]=t[u*2]+t[u*2+1];
	return ;
}

int _query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)/2,sum=0;
	if (al<=mid)
		sum+=_query(u*2,l,mid,al,ar);
	if (ar>mid)
		sum+=_query(u*2+1,mid+1,r,al,ar);
	return sum;
}

void solve(int l,int r,long long cl,long long cr)
{
	if (l>=r || cl>=cr)
		return ;

	long long cmid=(cl+cr)/2;
	int nl=l,nr=l;
	long long c0=-INF,c1=INF;
	// cerr << "*****" << l << '-' << r << "*****\n";
	for (int i=l;i<=r;i++)
	{
		// cerr << "&& " << q[i].i << "  " << q[i].t << " : ";
		if (q[i].t)
		{
			if (q[i].c<=cmid)
				_add(1,1,Maxk,q[i].k,1),col[i]=0,nr++;
			else
				col[i]=1;
		}
		else
		{
			if (q[i].c<=cmid)
				col[i]=0,nr++;
			else
			{
				// cerr << _query(1,1,Maxk,1,q[i].k);
				ans+=_query(1,1,Maxk,1,q[i].k),col[i]=1;
			}
		}
		// cerr << endl;
	}
	int mid=nr-1;
//	printf("## %d : %lld %lld\n",mid,cl,cr);
	for (int i=l;i<=r;i++)
		if (q[i].t && q[i].c<=cmid)
			_add(1,1,Maxk,q[i].k,-1);
	for (int i=l;i<=r;i++)
		if (col[i])
			nq[nr++]=q[i],c1=min(c1,q[i].c);
		else
			nq[nl++]=q[i],c0=max(c0,q[i].c);
	for (int i=l;i<=r;i++)
		q[i]=nq[i];
	solve(l,mid,cl,cmid);
	solve(mid+1,r,cmid+1,cr);
	return ;
}

int main()
{
	freopen("2707.in","r",stdin);
	freopen("2707.out","w",stdout);
	long long Minc=INF,Maxc=-INF;
	int tot,m1,m2;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<n;i++)
		scanf("%d",&b[i]);
	for (int i=0;i<n;i++)
		scanf("%d",&c[i]);
	m1=n/2;
	m2=n-m1;
	tot=(1<<m1);
	calc(0,m1,0);
	calc(tot,m2,m1);
	for (int i=0;i<(1<<m2);i++)
	{
		q[i+tot].k=k-q[i+tot].k;
		q[i+tot].b*=-1;
		q[i+tot].c*=-1;
		q[i+tot].t=1;
	}
	for (int i=0;i<(1<<m1)+(1<<m2);i++)
	{
		// cerr << "## " << q[i].i << " : " << q[i].b << " " << q[i].c << " " << q[i].k << endl;
		Minc=min(Minc,q[i].c),Maxc=max(Maxc,q[i].c);
		Mink=min(Mink,q[i].k),Maxk=max(Maxk,q[i].k);
	}
	if (Minc<0)
	{
		for (int i=0;i<(1<<m1)+(1<<m2);i++)
			q[i].c-=Minc;
		Maxc-=Minc;
		Minc-=Minc;
	}
	if (Mink<=0)
	{
		for (int i=0;i<(1<<m1)+(1<<m2);i++)
			q[i].k-=Mink-1;
		Maxk-=Mink-1;
		Mink-=Mink-1;
	}
	sort(q,q+(1<<m1)+(1<<m2),_cmp);
//	for (int i=0;i<(1<<m1)+(1<<m2);i++)
		// cerr << "^^ " << q[i].i << " : " << q[i].b << " " << q[i].c << " " << q[i].k << endl;
	// cerr << "%% " << Minc << ' ' << Maxc << endl;
	solve(0,(1<<m1)+(1<<m2)-1,Minc,Maxc);
	printf("%lld\n",ans);
	return 0;
}