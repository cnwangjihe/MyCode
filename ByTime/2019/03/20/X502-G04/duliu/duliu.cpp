#include <bits/stdc++.h>

using namespace std;

typedef pair<int,short> pis;

const int INF  = 300009,
		  MAXN = 300009;
const short L  = 0,
		    R  = 1,
		    LR = 2;
const pis RNone = make_pair(-1,LR),
		  LNone = make_pair(INF,LR);

struct Tnode{
	long long Max;
	int lc,rc;
	pis Lef,Rig;
	Tnode(){lc=rc=0;Lef=LNone;Rig=RNone;Max=0;}
};

struct Td{int d,p;};

struct PST
{
	Tnode t[MAXN*51];
	int ext[MAXN];
	int fp;
	PST(){fp=1;}
	inline int New(int u) {return t[fp]=t[u],fp++;}
	inline void Up(int u)
	{
		t[u].Lef=min(t[t[u].lc].Lef,t[t[u].rc].Lef);
		t[u].Rig=max(t[t[u].lc].Rig,t[t[u].rc].Rig);
		t[u].Max=max(t[t[u].lc].Max,t[t[u].rc].Max);
		return ;
	}
	pis AskLefPos(int u,int l,int r,int p)
	{
		if (!u)
			return RNone;
		if (l==r)
			return t[u].Rig;
		int mid=(l+r)>>1;
		if (p<=mid)
			return AskLefPos(t[u].lc,l,mid,p);
		else
		{
			pis ans=AskLefPos(t[u].rc,mid+1,r,p);
			if (t[u].lc)
				return max(ans,t[t[u].lc].Rig);
			else
				return ans; 
		}
		return RNone;
	}
	pis AskRigPos(int u,int l,int r,int p)
	{
		if (!u)
			return LNone;
		if (l==r)
			return t[u].Lef;
		int mid=(l+r)>>1;
		if (p>mid)
			return AskRigPos(t[u].rc,mid+1,r,p);
		else
		{
			pis ans=AskRigPos(t[u].lc,l,mid,p);
			if (t[u].rc)
				return min(ans,t[t[u].rc].Lef);
			else
				return ans;
		}
		return LNone;
	}
	long long AskMax(int u,int l,int r,int al,int ar)
	{
		if (al>ar)
			return 0;
		if (!u)
			return 0;
		if (al<=l && ar>=r)
			return t[u].Max;
		int mid=(l+r)>>1;
		long long ans=0;
		if (al<=mid)
			ans=max(ans,AskMax(t[u].lc,l,mid,al,ar));
		if (ar>mid)
			ans=max(ans,AskMax(t[u].rc,mid+1,r,al,ar));
		return ans;
	}
	void Modify(int &u,int l,int r,int p,int v,long long s,short w)
	{
		u=New(u);
		if (l==r)
		{
			ext[l]=v;
			t[u].Max=s;
			if (!ext[l])
				t[u].Lef=LNone,t[u].Rig=RNone;
			else
				t[u].Lef=t[u].Rig=make_pair(l,w);
			return ;
		}
		int mid=(l+r)>>1;
		if (p<=mid)
			Modify(t[u].lc,l,mid,p,v,s,w);
		else
			Modify(t[u].rc,mid+1,r,p,v,s,w);
		Up(u);
		return ;
	}
};

PST PST;
Td d[MAXN];
int ans[MAXN],root[MAXN];
int lg2[MAXN];
int Min[20][MAXN];
long long sum[MAXN];
bool ext[MAXN];
int n,m=0,q;

inline bool _cmp(Td a,Td b) {return a.d>b.d;}

void Pre()
{
	sort(d+1,d+1+n,_cmp);
	PST.Modify(root[0],1,n,1,1,(sum[n]-sum[0])*n*2,L);
	PST.Modify(root[0],1,n,n,1,(sum[n]-sum[0])*n*2,R);
	ext[0]=ext[n+1]=1;
	int l,r,p,i;
	for (int j=1;j<=n;)
	{
		i=j;
	//	cerr << i << '\n';
		ans[m++]=d[i].d;
		root[m]=root[m-1];
		for (;j<=n && d[j].d==d[i].d;j++)
		{
			p=d[j].p;
			if (ext[p+1] && ext[p-1])
				PST.Modify(root[m],1,n,p,0,0,L);
			else if (!ext[p+1] && !ext[p-1])
			{
				l=PST.AskLefPos(root[m],1,n,p).first;
				r=PST.AskRigPos(root[m],1,n,p).first;
		//		printf("### %d %d,%d\n",p,l,r);
				PST.Modify(root[m],1,n,l,1,(sum[p-1]-sum[l-1])*(p-l)*2,(p-1==l)?LR:L);
				PST.Modify(root[m],1,n,r,1,(sum[r]-sum[p])*(r-p)*2,(p+1==r)?LR:R);
				if (p-1!=l)
					PST.Modify(root[m],1,n,p-1,1,(sum[p-1]-sum[l-1])*(p-l)*2,R);
				if (p+1!=r)
					PST.Modify(root[m],1,n,p+1,1,(sum[r]-sum[p])*(r-p)*2,L);
			}
			else if (ext[p+1] && !ext[p-1])
			{
				l=PST.AskLefPos(root[m],1,n,p-1).first;
			//	printf("### %d %d\n",p,l);
				PST.Modify(root[m],1,n,p,0,0,L);
				PST.Modify(root[m],1,n,l,1,(sum[p-1]-sum[l-1])*(p-l)*2,(p-1==l)?LR:L);
				if (p-1!=l)
					PST.Modify(root[m],1,n,p-1,1,(sum[p-1]-sum[l-1])*(p-l)*2,R);
			}
			else if (!ext[p+1] && ext[p-1])
			{
				r=PST.AskRigPos(root[m],1,n,p+1).first;
				PST.Modify(root[m],1,n,p,0,0,L);
				PST.Modify(root[m],1,n,r,1,(sum[r]-sum[p])*(r-p)*2,(p+1==r)?LR:R);
				if (p+1!=r)
					PST.Modify(root[m],1,n,p+1,1,(sum[r]-sum[p])*(r-p)*2,L);
			}
			ext[p]=1;
		}
	}
	return ;
}

bool Check(int l,int r,int k,long long v)
{
	long long Max=0;
	pis lr=PST.AskRigPos(root[k],1,n,l),
		rl=PST.AskLefPos(root[k],1,n,r);
//	printf("%d,%d %d:\n",l,r,k);
//	printf("%d,%d %d,%d\n",lr.first,lr.second,rl.first,rl.second);
	lr.first=min(lr.first,r);
//	printf("%d,%d %d,%d\n",lr.first,lr.second,rl.first,rl.second);
	rl.first=max(rl.first,l);
	if (lr.second==R)
		Max=max(Max,(sum[lr.first]-sum[l-1])*(lr.first-l+1)*2);
	if (rl.second==L)
		Max=max(Max,(sum[r]-sum[rl.first-1])*(r-rl.first+1)*2);
	if (lr.second!=R && rl.second!=L)
		Max=max(Max,PST.AskMax(root[k],1,n,lr.first,rl.first));
	else if (lr.second!=R && rl.second==L)
		Max=max(Max,PST.AskMax(root[k],1,n,lr.first,rl.first-1));
	else if (lr.second==R && rl.second!=L)
		Max=max(Max,PST.AskMax(root[k],1,n,lr.first+1,rl.first));
	else
		Max=max(Max,PST.AskMax(root[k],1,n,lr.first+1,rl.first-1));
//	printf("%lld %lld\n",Max,PST.AskMax(root[k],1,n,lr.first+1,rl.first-1));
	return Max>=v;
}

void RMQ()
{
	int m=lg2[n];
	for (int i=1;i<=n;i++)
		Min[0][i]=d[i].d;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (j+(1<<i)-1<=n)
				Min[i][j]=min(Min[i-1][j],Min[i-1][j+(1<<(i-1))]);
	return ;
}

int query(int l,int r)
{
	int len=lg2[r-l+1];
	return min(Min[len][l],Min[len][r-(1<<len)+1]);
}

void prelg2()
{
	lg2[1]=0;
	for (int i=2;i<=n;i++)
		lg2[i]=lg2[i/2]+1;
	return ;
}

int Calc(int al,int ar,long long v)
{
	int l=-1,r=m,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (Check(al,ar,mid,v))
			l=mid;
		else
			r=mid;
	}
	return (l==-1)?-1:ans[l];
}

void force1()
{
	Pre();
	int l,r;
	long long x;
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%lld",&l,&r,&x);
		if (x==1ll)
			printf("%d\n",query(l,r));
		else
			printf("%d\n",Calc(l,r,x));
	}
	return ;
}

void force5()
{
	int l,r;
	long long x;
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%lld",&l,&r,&x);
		printf("%d\n",((sum[r]-sum[l-1])*(r-l+1)*2>=x)?1:-1);
	}
	return ;
}

int main()
{
//	freopen("duliu.in","r",stdin);
//	freopen("duliu.out","w",stdout);
//	cerr << (sizeof PST)+(sizeof Min) << '\n';
	scanf("%d%d",&n,&q);
	bool sub5=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&d[i].d),d[i].p=i;
		if (d[i].d!=1)
			sub5=0;
	}
	for (int i=1;i<=n;i++)
		sum[i]=sum[i-1]+d[i].d;
	if (sub5)
		return force5(),0;
	prelg2();
	RMQ();
	force1();
	return 0;
}