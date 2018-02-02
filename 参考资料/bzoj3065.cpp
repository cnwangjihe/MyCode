#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 70000;
const int M = 275;
const int MAXM = 550;
int n,m;
int ans=0;
struct lump
{
	lump *last,*next;
	int tot;
	int val[MAXM+1];
	int cc[N+1],cx[M+1];
}xu[M+1],*s;
int cc[N+1],cx[M+1];
int cnt=0;
int getint()
{
	int res=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')
		ch=getchar();
	while('0'<=ch && ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
char getopt()
{
	char ch=getchar();
	while(ch<'A' || ch>'Z')
		ch=getchar();
	return ch;
}
void GetData()
{
	int i,j;
	n=getint();
	for(i=1;i<=n;i++)
	{
		int z=getint();
		xu[i/M+1].tot++;
		xu[i/M+1].val[xu[i/M+1].tot]=z;
		xu[i/M+1].cc[z]++;
		xu[i/M+1].cx[z/M]++;
	}
	cnt=n/M+1;
	for(i=0;i<cnt;i++)
		xu[i].next=xu+(i+1);
	for(i=1;i<=cnt;i++)
		xu[i].last=xu+(i-1);
	for(i=1;i<=cnt;i++)
	{
		for(j=0;j<=N;j++)
			xu[i].cc[j]+=xu[i-1].cc[j];
		for(j=0;j<=M;j++)
			xu[i].cx[j]+=xu[i-1].cx[j];
	}
}
void Change(int x,int y)
{
	lump *now=xu;
	while(now->tot<x)
	{
		x-=now->tot;
		now=now->next;
	}
	int z=now->val[x];
	now->val[x]=y;
	while(now)
	{
		now->cc[y]++;
		now->cc[z]--;
		now->cx[y/M]++;
		now->cx[z/M]--;
		now=now->next;
	}
}
int Find(int l,int r,int x)
{
	int i;
	lump *a,*b;
	a=xu;
	while(a->tot<l)
	{
		l-=a->tot;
		a=a->next;
	}
	b=xu;
	while(b->tot<r)
	{
		r-=b->tot;
		b=b->next;
	}
	memset(cx,0,sizeof cx);
	for(i=1;i<l;i++)
		cx[a->val[i]/M]--;
	for(i=1;i<=r;i++)
		cx[b->val[i]/M]++;
	a=a->last;
	b=b->last;
	for(i=0;;i++)
	{
		if(x<=b->cx[i]+cx[i]-a->cx[i])
			break;
		x-=b->cx[i]+cx[i]-a->cx[i];
	}
	int zl=i*M;
	int zr=min(N,zl+M-1);
	memset(cc+zl,0,sizeof(int)*(zr-zl+1));
	a=a->next;
	b=b->next;
	for(i=1;i<l;i++)
		cc[a->val[i]]--;
	for(i=1;i<=r;i++)
		cc[b->val[i]]++;
	a=a->last;
	b=b->last;
	for(i=zl;;i++)
	{
		if(x<=b->cc[i]+cc[i]-a->cc[i])
			break;
		x-=b->cc[i]+cc[i]-a->cc[i];
	}
	return i;
}
void Big(lump *x)
{
	if(x->tot==MAXM)
	{
		cnt++;
		int i;
		for(i=0;i<=M;i++)
			xu[cnt].cx[i]=x->cx[i];
		for(i=0;i<=N;i++)
			xu[cnt].cc[i]=x->cc[i];
		for(i=1;i<=M;i++)
			xu[cnt].val[i]=x->val[i];
		for(i=M+1;i<=MAXM;i++)
		{
			x->val[i-M]=x->val[i];
			xu[cnt].cc[x->val[i]]--;
			xu[cnt].cx[x->val[i]/M]--;
		}
		xu[cnt].tot=M;
		x->tot=M;
		xu[cnt].last=x->last;
		x->last->next=xu+cnt;
		xu[cnt].next=x;
		x->last=xu+cnt;
	}
}
void Insert(int x,int y)
{
	lump *now=xu->next;
	while(now->tot<x-1)
	{
		x-=now->tot;
		now=now->next;
	}
	int i;
	now->tot++;
	for(i=now->tot;i>x;i--)
		now->val[i]=now->val[i-1];
	now->val[x]=y;
	lump *jie=now;
	while(now)
	{
		now->cc[y]++;
		now->cx[y/M]++;
		now=now->next;
	}
	Big(jie);
}
void DoIt()
{
	char t;
	int a,b,c;
	m=getint();
	while(m--)
	{
		t=getopt();
		a=getint()^ans;
		b=getint()^ans;
		if(t=='M')
			Change(a,b);
		else if(t=='Q')
		{
			c=getint()^ans;
			ans=Find(a,b,c);
			printf("%d\n",ans);
		}
		else
			Insert(a,b);
	}
}
int main()
{
	GetData();
	DoIt();
	return 0;
}
