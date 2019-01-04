#include <bits/stdc++.h>
using namespace std;

#define lc child[x][0]
#define rc child[x][1]

typedef long long ll;
const int mod=51061;
const int mx=1e5+10;

struct LCT
{
	int fa[mx],child[mx][2],rev[mx],size[mx];
	ll sum[mx],add[mx],val[mx],mul[mx],fmul[mx];
	void pup(int x)
	{
		if(!x) return ;
		sum[x]=val[x],size[x]=1;
		if(lc) sum[x]+=sum[lc],size[x]+=size[lc];
		if(rc) sum[x]+=sum[rc],size[x]+=size[rc];
	}
	void qmul(int x,ll v)
	{
		if(!x) return ;
		fmul[x]=1;
		(val[x]*=v)%=mod;
		(sum[x]*=v)%=mod;
		(add[x]*=v)%=mod;
		(mul[x]*=v)%=mod;
	}
	void qadd(int x,ll v)
	{
		if(!x) return ;
		(val[x]+=v)%=mod;
		(sum[x]+=v*size[x])%=mod;
		(add[x]+=v)%=mod;
	}
	void sadd(int x,ll v1,ll v2,int v3)
	{
		if(!x) return ;
		if(v3)
		{
			fmul[x]=1;
			(val[x]*=v2)%=mod;
			(sum[x]*=v2)%=mod;
			(add[x]*=v2)%=mod;
			(mul[x]*=v2)%=mod;
		}
		(val[x]+=v1)%=mod;
		(sum[x]+=v1*size[x])%=mod;
		(add[x]+=v1)%=mod;
	}
	void srev(int x,int v)
	{
		if(!x) return ;
		if(v) rev[x]^=1,swap(lc,rc);
	}
	void pdown(int x)
	{
		if(!x) return ;
		if(lc) sadd(lc,add[x],mul[x],fmul[x]),srev(lc,rev[x]);
		if(rc) sadd(rc,add[x],mul[x],fmul[x]),srev(rc,rev[x]);
		add[x]=0,rev[x]=0,fmul[x]=0,mul[x]=1;
	}
	void link(int fat,int son,int is)
	{
		if(son) fa[son]=fat;
		if(fat) child[fat][is]=son;
	}
	bool is(int x)
	{
		return child[fa[x]][1]==x;
	}
	bool isroot(int x)
	{
		return child[fa[x]][0]!=x && child[fa[x]][1]!=x;
	}
	void rotate(int x)
	{
		if(!x) return ;
		int y=fa[x],z=fa[y],isx=is(x),isy=is(y);
		if(isroot(y)) fa[x]=z;
		else link(z,x,isy);
		link(y,child[x][!isx],isx);
		link(x,y,!isx);
		pup(y),pup(x),pup(z);
	}
	void push(int x)
	{
		if(!isroot(x)) push(fa[x]);
		pdown(x);
	}
	void splay(int x)
	{
		if(!x) return ;
		push(x);
		int y;
		while(!isroot(x))
		{
			y=fa[x];
			if(isroot(y))
			{
				rotate(x);
				break;
			}
			if(is(x)==is(y)) rotate(y),rotate(x);
			else rotate(x),rotate(x);
		}
		pup(x);
	}
	void access(int x)
	{
		int t=0;
		while(x)
		{
			splay(x);
			rc=t;
			t=x;
			x=fa[x];
		}
	}
	void makeroot(int x)
	{
		if(!x) return ;
		access(x);
		splay(x);
		srev(x,1);
	}
	void connect(int x,int y)
	{
		makeroot(x);
		fa[x]=y;
	}
	void cut(int x,int y)
	{
		makeroot(x);
		access(y);
		splay(y);
		child[y][0]=fa[x]=0;
	}
	ll ask(int x,int y)
	{
		makeroot(x);
		access(y);
		splay(y);
		return sum[y];
	}
	void madd(int x,int y,ll v)
	{
		makeroot(x);
		access(y);
		splay(y);
		qadd(y,v);
	}
	void mmul(int x,int y,ll v)
	{
		makeroot(x);
		access(y);
		splay(y);
		qmul(y,v);
	}
};
LCT lct;
int n,q;


int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&q);

	for(int i=1;i<=n;i++)
	{
		lct.val[i]=1;
		lct.pup(i);
	}

	int u1,u2,v1,v2,c;
	ll ans=0;
	
	for(int i=0;i<n-1;i++)
	{
		scanf("%d%d",&u1,&v1);
		lct.connect(u1,v1);
	}
	
/*	lct.madd(1,2,2);
	lct.mmul(2,3,3);
	cerr<<lct.ask(1,3)<<endl;
*/	
	char ch=0;
	for(int i=0;i<q;i++)
	{
		do ch=getchar();
		while(ch!='+' && ch!='-' && ch!='*' && ch!='/');
		if(ch=='+')
		{
			scanf("%d%d%d",&u1,&v1,&c);
			lct.madd(u1,v1,c);
		}
		if(ch=='-')
		{
			scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
			lct.cut(u1,v1);
			lct.connect(u2,v2);
		}
		if(ch=='*')
		{
			scanf("%d%d%d",&u1,&v1,&c);
//			cerr<<u1<<" "<<v1<<" "<<lct.ask(u1,v1)<<endl;
			lct.mmul(u1,v1,c);
//			cerr<<u1<<" "<<v1<<" "<<lct.ask(u1,v1)<<endl;
		}
		if(ch=='/')
		{
			scanf("%d%d",&u1,&v1);
			ans=lct.ask(u1,v1)%mod;
			printf("%lld\n",ans);
		}
	}
	

	
	return 0;
}
