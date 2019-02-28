// Date      : 2019-02-26 08:04:40
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXQ = MAXN,
		  INF  = 1000000009;

struct Tquery {int sx,sy,ex,ey,i;};

Tquery q1[MAXQ],q2[MAXQ];
pair<int,int> s[MAXN];
int ans[MAXQ],a[MAXN];
int n,q,c1,c2,top=0;

bool _cmp(Tquery a,Tquery b) {return a.ex<b.ex;}

int FindPos(int p)
{
	int l=-1,r=top,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (s[mid].second>p)
			r=mid;
		else
			l=mid;
	}
	return r;
}

int FindValue(int v)
{
	int l=-1,r=top,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (s[mid].first>v)
			r=mid;
		else
			l=mid;
	}
	return r;
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]++;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d%d",&q1[c1].sx,&q1[c1].sy,&q1[c1].ex,&q1[c1].ey);
		q1[c1].sy++,q1[c1].ey++,q1[c1].i=i;
		if (q1[c1].sx>=q1[c1].ex)
			q2[c2++]=q1[c1];
		else
			c1++;
	}
	sort(q1+0,q1+c1,_cmp);
	int p=0;
	for (int i=0;i<c1;i++)
	{
		while (p<q1[i].ex)
		{
			p++;
			while (top && s[top-1].first>=a[p])
				top--;
			s[top++]=make_pair(a[p],p);
		}
		s[top]=make_pair(INF,p+1);
		int tp=FindPos(q1[i].sx),tv=FindValue(q1[i].ey);
		int sum=0;
		if (s[tv-1].second>=q1[i].sx && abs(s[tv].first-q1[i].ey)>abs(s[tv-1].first-q1[i].ey))
			tv--;
		/*down+end+rl*/
		if (tp==tv && q1[i].sy>=s[tp].first)
			sum--;
		sum+=q1[i].ex-q1[i].sx+1;
		sum+=abs(s[tv].first-q1[i].ey);
		ans[q1[i].i]=sum;
		/*down+rl*/
		sum=q1[i].ex-q1[i].sx;
		sum+=abs(min(q1[i].sy,s[tp].first)-q1[i].ey);
		ans[q1[i].i]=min(ans[q1[i].i],sum);
		/*Home+down+r*/
		sum=q1[i].ex-q1[i].sx+1;
		sum+=q1[i].ey-1;
		ans[q1[i].i]=min(ans[q1[i].i],sum);
	}
	top=0;
	for (int i=1;i*2<=n;i++)
		swap(a[i],a[n-i+1]);
	for (int i=0;i<c2;i++)
		q2[i].sx=n-q2[i].sx+1,q2[i].ex=n-q2[i].ex+1;
	sort(q2+0,q2+c2,_cmp);
	p=0;
	for (int i=0;i<c2;i++)
	{
		while (p<q2[i].ex)
		{
			p++;
			while (top && s[top-1].first>=a[p])
				top--;
			s[top++]=make_pair(a[p],p);
		}
		s[top]=make_pair(INF,p+1);
		int tp=FindPos(q2[i].sx),tv=FindValue(q2[i].ey);
		int sum=0;
		if (s[tv-1].second>=q2[i].sx && abs(s[tv].first-q2[i].ey)>abs(s[tv-1].first-q2[i].ey))
			tv--;
		/*down+end+rl*/
		if (tp==tv && q2[i].sy>=s[tp].first)
			sum--;
		sum+=q2[i].ex-q2[i].sx+1;
		sum+=abs(s[tv].first-q2[i].ey);
		ans[q2[i].i]=sum;
		/*down+rl*/
		sum=q2[i].ex-q2[i].sx;
		sum+=abs(min(q2[i].sy,s[tp].first)-q2[i].ey);
		ans[q2[i].i]=min(ans[q2[i].i],sum);
		/*Home+down+r*/
		sum=q2[i].ex-q2[i].sx+1;
		sum+=q2[i].ey-1;
		ans[q2[i].i]=min(ans[q2[i].i],sum);
	}
	for (int i=0;i<q;i++)
		printf("%d\n",ans[i]);
	return 0;
}