#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN=1000100;

typedef long long LL;

LL Sum[MAXN];
LL Order[MAXN];
int A[MAXN];
int n,P,m;

int c[MAXN];
void Update(int x);
int Query(int x);
int ReadInt();

int main()
{

	n=ReadInt();
	for (int i=1;i<=n;++i) A[i]=ReadInt();
	P=ReadInt();
	for (int i=1;i<=n;++i) Sum[i]=Sum[i-1]+A[i]-P;
	for (int i=0;i<=n;++i) Order[i+1]=Sum[i];

	sort(Order+1,Order+2+n);
	for (int i=1;i<=m;i++)
		cerr << Order[i] << ' ';
	cerr << '\n';
	m=unique(Order+1,Order+2+n)-Order-1;
	for (int i=1;i<=m;i++)
		cerr << Order[i] << ' ';
	cerr << '\n';
	LL ans=0;
	for (int i=0;i<=n;++i)
	{
		int p=lower_bound(Order+1,Order+1+m,Sum[i])-Order;
		ans+=Query(p);
		Update(p);
		cerr << i << ' ' << p << ' ' << ans << endl;
	}
	cout << ans << endl;

	return 0;
}
void Update(int x) { for (;x<=m;x+=x&-x) c[x]++; }
int Query(int x) {int ans=0;for (;x>0;x-=x&-x) ans+=c[x];return ans;}
int ReadInt()
{
	int num=0;char c=getchar();
	while (c<'0' || c>'9') c=getchar();
	while (c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
	return num;
}

