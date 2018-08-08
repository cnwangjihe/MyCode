#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 100009;

char s[MAXN];
int t[MAXN*4];
int rank[MAXN],sa[MAXN],temp[MAXN];
int height[MAXN],cnt[MAXN];
int n,m=26,ans=0,k;

void _add(int u,int l,int r,int p)
{
	if (l==r)
	{
		t[u]++;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_add(u*2,l,mid,p);
	else
		_add(u*2+1,mid+1,r,p);
	t[u]=t[u*2]+t[u*2+1];
	return ;
}

int _ask(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)/2,ans=0;
	if (al<=mid)
		ans+=_ask(u*2,l,mid,al,ar);
	if (ar>mid)
		ans+=_ask(u*2+1,mid+1,r,al,ar);
	return ans;
}

bool _cmp(int *r,int a,int b,int len)
{
	if((a+len<n)!=(b+len<n) || r[a]!=r[b]) return 0;
	return ((a+len<n)?(r[a+len]==r[b+len]):1); 
}

void _getrank(int n,int m)
{
	int j,p;
	for (int i=0;i<m;i++) cnt[i]=0;
	for (int i=0;i<n;i++) cnt[rank[i]=s[i]-'a']++;
	for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for (int i=n-1;i>=0;i--) sa[--cnt[rank[i]]]=i;
	for (j=1,p=1;p<n;m=p,j=j*2)
	{
		p=0;
		for (int i=n-j;i<n;i++) temp[p++]=i;
		for (int i=0;i<n;i++) if (sa[i]>=j) temp[p++]=sa[i]-j;
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[temp[i]]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;i>=0;i--) sa[--cnt[rank[temp[i]]]]=temp[i];
		swap(rank,temp);
		rank[sa[0]]=0;
		p=1;
		for (int i=1;i<n;i++)
			rank[sa[i]]=_cmp(temp,sa[i-1],sa[i],j)?p-1:p++;
	}
}


void _getheight(int *rank,int *sa,int *height,char *s,int n)
{
	
	int x=0,j;
	for (int i=0;i<n;i++)
	{
		if (x>0) x--;
		if (rank[i]==0) continue;
		j=sa[rank[i]-1];
		while (i+x<n && j+x<n && s[i+x]==s[j+x]) x++;
		height[rank[i]]=x;
	}
}

int main()
{
	freopen("2464.in","r",stdin);
	freopen("2464.out","w",stdout);
	scanf("%d%d%s",&n,&k,s);
	_getrank(n,m);
	_getheight(rank,sa,height,s,n);
	int j;
//	for  (int i=0;i<n;i++)
//		cerr << sa[i] << ' ' << rank[i] << '\n';
	for (int i=1;i<n;i=j+1)
	{
		for (j=i;height[j]>=k && j<n;j++);
		sort(sa+i-1,sa+j);
	}
	for(int i=0;i<n;i++)
	{
	//	cerr << sa[i] << endl;
		sa[i]++;
		ans+=i-_ask(1,1,n,1,sa[i]);
		_add(1,1,n,sa[i]);
	}
	printf("%d\n",ans);
}
