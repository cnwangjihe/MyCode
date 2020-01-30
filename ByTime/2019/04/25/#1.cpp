// Date      : 2019-01-03 11:37:21
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P2408
// Algorithm : SA
// Notice    : Please look at line 72-76

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009,
		  MAXM = 29;

char s[MAXN];
int rank[MAXN],sa[MAXN],tmp[MAXN],h[MAXN];
int cnt[MAXN];
int n,m=27;
long long ans=0;

inline bool _cmp(int *r,int a,int b,int len) {return (r[a]==r[b] && r[a+len]==r[b+len]);}

void _getrank(int *rank,int *sa,int *tmp,int n,int m)
{
	for (int i=0;i<m;i++) cnt[i]=0;
	for (int i=0;i<n;i++) cnt[rank[i]]++;
	for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for (int i=n-1;~i;i--) sa[--cnt[rank[i]]]=i;
	for (int j=1,p=1;p<n;m=p,j*=2)
	{
		p=0;
		for (int i=n-j;i<n;i++) tmp[p++]=i;
		for (int i=0;i<n;i++) if (sa[i]>=j) tmp[p++]=sa[i]-j;
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[tmp[i]]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;~i;i--) sa[--cnt[rank[tmp[i]]]]=tmp[i];
		for (int i=0;i<n;i++) swap(tmp[i],rank[i]);
		rank[sa[0]]=0;
		p=1;
		for (int i=1;i<n;i++)
			rank[sa[i]]=_cmp(tmp,sa[i-1],sa[i],j)?p-1:p++;
	}
	return ;
}
	
void _getheight(int *rank,int *sa,int *height,char *s,int n)
{
	int x=0,j;
	for (int i=0;i<n;i++)
	{
		x-=(x>0);
		if (!rank[i])
			continue;
		j=sa[rank[i]-1];
		while (s[i+x]==s[j+x])
			x++;
		height[rank[i]]=x;
	}
	return ;
}

int main()
{
//	freopen("P2408.in","r",stdin);
//	freopen("P2408.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s);
	fill(s+n,s+MAXN,-1);
	fill(tmp+0,tmp+MAXN,-1);
	for (int i=0;i<n;i++)
		rank[i]=(s[i]-='a');
	fill(rank+n,rank+MAXN,-1);
	_getrank(rank,sa,tmp,n,m);
	_getheight(rank,sa,h,s,n);
	for (int i=0;i<n;i++)
		cerr << i << ' ' << rank[i] << ' ' << sa[i] << ' ' << h[i] << '\n';
	for (int i=0;i<n;i++)
		ans+=h[i];
	printf("%lld\n",1ll*n*(n+1)/2-ans);
	return 0;
}