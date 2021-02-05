// Date      : 2019-03-14 08:51:06
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : SegmentTree
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXP = (1<<18)*18*4;

struct Node {int v,l,r;Node(){v=l=r=0;}};

struct Pool
{
	Node node[MAXP];
	int fp;
	Pool(){fp=1;}
	Node& operator[](int u) {return node[u];}
	inline int New() {return fp++;}
};

struct SegmentTree
{
	Pool *t;
	SegmentTree() {}
	void Set(Pool *a){t=a;}
	inline void Up(int u) {(*t)[u].v=(*t)[(*t)[u].l].v+(*t)[(*t)[u].r].v;}
	void Modify(int &u,int l,int r,int p,int v)
	{
		if (!u)
			u=t->New();
		if (l==r)
			return (void)((*t)[u].v+=v);
		int mid=(l+r)>>1;
		if (p<=mid)
			Modify((*t)[u].l,l,mid,p,v);
		else
			Modify((*t)[u].r,mid+1,r,p,v);
		Up(u);
		return ;
	}
	int Query(int &u,int l,int r,int al,int ar)
	{
		if (!u)
			return 0;
		if (al<=l && ar>=r)
			return (*t)[u].v;
		int mid=(l+r)>>1,ans=0;
		if (al<=mid)
			ans+=Query((*t)[u].l,l,mid,al,ar);
		if (ar>mid)
			ans+=Query((*t)[u].r,mid+1,r,al,ar);
		return ans;
	}
};

Pool P;
SegmentTree ST[18];
int d=0,n=(1<<18);
int root[18];
map<int,int> m;
int q;

int main()
{
	// freopen("bitcoin.in","r",stdin);
	// freopen("bitcoin.out","w",stdout);
	scanf("%d",&q);
	int t,x,v,tmp;
	for (int i=0;i<18;i++)
		ST[i].Set(&P);
	for (int i=0;i<q;i++)
	{
		scanf("%d%d",&t,&x);
		if (t==0)
		{
			v=x-d,m[v]++;
			for (int i=0;i<18;i++)
				ST[i].Modify(root[i],1,n,(v&((1<<(i+1))-1))+1,1);
		}
		else if (t==1)
		{
			v=x-d,tmp=m[v];
			for (int i=0;i<18;i++)
				ST[i].Modify(root[i],1,n,(v&((1<<(i+1))-1))+1,-tmp);
			m[v]=0;
		}
		else if (t==2)
			d+=x;
		else if (t==3)
		{
			int l=1<<x,r=(1<<(x+1))-1,ans=0;
		//	cout << max(0,min(1<<18,l-(d&((1<<(x+1))-1))))+1 << ',' << max(0,min(1<<18,r-(d&((1<<(x+1))-1))))+1 << '\n';
			ans+=ST[x].Query(root[x],1,n,max(0,min(1<<18,l-(d&((1<<(x+1))-1))))+1,max(0,min(1<<18,r-(d&((1<<(x+1))-1))))+1);
			l+=1<<(x+1), r+=1<<(x+1);
			ans+=ST[x].Query(root[x],1,n,max(0,min(1<<18,l-(d&((1<<(x+1))-1))))+1,max(0,min(1<<18,r-(d&((1<<(x+1))-1))))+1);
			printf("%d\n",ans);
		}
	}
	return 0;
}