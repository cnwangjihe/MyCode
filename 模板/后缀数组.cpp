bool _cmp(int *r,int a,int b,int len)
{ return (r[a]==r[b] && r[a+len]==r[b+len]); }

void _getrank(int *rank,int *sa,int n,int m)
{
	int j,p,*tmp=temp,*yu;
	for (int i=0;i<m;i++) cnt[i]=0;
	for (int i=0;i<n;i++) cnt[rank[i]]++;
	for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for (int i=n-1;i>=0;i--) sa[--cnt[rank[i]]]=i;
	for (j=1,p=1;p<n;m=p,j=j*2)
	{
		p=0;
		for (int i=n-j;i<n;i++) tmp[p++]=i;
		for (int i=0;i<n;i++) if (sa[i]>=j) tmp[p++]=sa[i]-j;
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[tmp[i]]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;i>=0;i--) sa[--cnt[rank[tmp[i]]]]=tmp[i];
		yu=tmp;tmp=rank;rank=yu;
		rank[sa[0]]=0;
		p=1;
		for (int i=1;i<n;i++)
			rank[sa[i]]=_cmp(tmp,sa[i-1],sa[i],j)?p-1:p++;
	}
}


void _getheight(int *rank,int *sa,int *height,int *s,int n)
{
	
	int x=0,j;
	for (int i=0;i<n;i++)
	{
		if (x>0) x--;
		if (rank[i]==0) continue;
		j=sa[rank[i]-1];
		while (s[i+x]==s[j+x]) x++;
		height[rank[i]]=x;
	}
}

/*
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;

const int MAXN = 100006 ;

struct T
{
	int x,y;
	T(){x=y=0;}
};

char s[100006];
bool f[MAXN];
int g[MAXN];
int Min[MAXN][22];
int sa[MAXN],rank[MAXN],c[MAXN],len[MAXN],px[MAXN];
T a[MAXN];
int i,j,x,k,n,y,z;

void RMQ()
{
	for (i=0;i<n;i++) Min[i][0] = len[i];
	for (j=1;j<20;j++)
		for(i=0;i<n;i++)
			if(i + (1 << j) - 1 <= n)
			{
				Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
			}
}

int RMQ_ask(int x,int y)
{
	int k=int(log2(y-x+1));
	return min(Min[x][k],Min[y-(1<<k)+1][k]);
}

bool _cmp(T a,T b) {return a.x<b.x;}

bool _sort(int l)
{
	int m=0;
	memset(c,0,sizeof c);
	for (i=0;i<n;i++) c[a[i].x]++;
	for (i=1;i<n;i++) c[i]+=c[i-1];
	for (m=0,i=n-l;i<n;i++,m++) px[m]=i;
	for (i=0;i<n;i++) if (sa[i]>=l) px[m++]=sa[i]-l;
	for (i=n-1;i>=0;i--) rank[px[i]] = --c[a[px[i]].x];
	for (i=0;i<n;i++) sa[rank[i]]=i;
	bool flag=1;
	for (i=1;i<n;i++)
	{
		if (a[sa[i]].x==a[sa[i-1]].x && a[sa[i]].y==a[sa[i-1]].y) rank[sa[i]]=rank[sa[i-1]],flag=0;
		else rank[sa[i]]=rank[sa[i-1]]+1;
	}
	return flag;
}

int main()
{
	memset(f,0,sizeof f);
	scanf("%s",s);
	n=strlen(s);
	s[n++]='#';
	
	for (i=0;i<n;i++) a[i].x=int(s[i])-'0',a[i].y=i;
	sort(a,a+n,_cmp);
	for (i=1;i<n;i++)
	{
		if (a[i].x==a[i-1].x) rank[a[i].y]=rank[a[i-1].y];
		else rank[a[i].y]=rank[a[i-1].y]+1;
	}
	for (i=0;i<n;i++) sa[i]=a[i].y;
	for (int l=1;;l<<=1)
	{
		for (int pos=0;pos<n;pos++)
		{
			a[pos].x = rank[pos];
			if (pos+l>=n) a[pos].y = 0;
			else a[pos].y = rank[pos+l];
		}
		if (_sort(l)) break;
	}
	x=0;
	for (i=0;i<n;i++)
	{
		if (x>0) x--;
		j=sa[rank[i]-1];
		while (s[i+x]==s[j+x]) x++;
		len[rank[i]]=x;
	}
	
	RMQ();
	for (;;)
	{
		scanf("%d%d",&y,&z);
		printf("%d\n",RMQ_ask(rank[y]+1,rank[z]));
	//	printf("%d\n",RMQ_ask(y+1,z));
	}
} */