// Date      : 2019-01-04 23:18:37
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1097/problem/F
// Algorithm : bitset,莫比乌斯反演
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009,
		  MAXV = 7009;

int n,m,k=0;
std::bitset<MAXV> A[MAXV],C[MAXV],B[MAXN];
int miu[MAXV],p[MAXV];
bool f[MAXV];

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int main()
{
//	freopen("CF1097F.in","r",stdin);
//	freopen("CF1097F.out","w",stdout);
	miu[1]=1;
	fill(f+0,f+MAXV,1);
	for (int i=2;i<MAXV;i++)
	{
		if (f[i])
			p[k++]=i,miu[i]=-1;
		for (int j=0;j<k && i*p[j]<MAXV;j++)
		{
			f[i*p[j]]=0;
			if (i%p[j])
				miu[i*p[j]]=-miu[i];
			else 
			{
				miu[i*p[j]]=0;
				break;
			}
		}
	}
	for (int i=1;i<MAXV;i++)
	{
		for (int j=1;j<=i;j++)
			if (!(i%j))
				A[i][j]=1;
		for (int j=i;j<MAXV;j+=i)
			C[i][j]=(miu[j/i]!=0);
	}
	n=read(),m=read();
	int x,y,t;
	for (int i=0;i<m;i++)
	{
		t=read(),x=read(),y=read();
		if (t==1)
			B[x]=A[y];
		if (t==2)
			B[x]=B[y]^B[read()];
		if (t==3)
			B[x]=B[y]&B[read()];
		if (t==4)
			putchar(48+((B[x]&C[y]).count()&1));
	}
	return 0;
}