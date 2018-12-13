// Date	: 2018-12-10 21:27:12
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link	: wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

struct Tquery{int t,l,r,k,i;};

Tquery q[MAXN+9];
bitset<MAXN+9> s1,s2;
int c[MAXN+9],a[MAXN+9],ans[MAXN+9],rt[MAXN+9];
int n,m,lim;

bool _cmp(Tquery A,Tquery B) {return rt[A.l]==rt[B.l]?rt[A.l]&1?A.r<B.r:A.r>B.r:rt[A.l]<rt[B.l];}

inline void _add(int v) {c[v]++;s1[v]=(c[v]!=0);s2[MAXN-v]=(c[v]!=0);}
inline void _del(int v) {c[v]--;s1[v]=(c[v]!=0);s2[MAXN-v]=(c[v]!=0);}

int main()
{
//	freopen("P3674.in","r",stdin);
//	freopen("P3674.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	lim=sqrt(n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<m;i++)
		scanf("%d%d%d%d",&q[i].t,&q[i].l,&q[i].r,&q[i].k),q[i].i=i,rt[i]=(i-1)/lim+1;

	sort(q,q+m,_cmp);

	int l=1,r=0;

	for (int i=0;i<m;i++)
	{
		for (;q[i].l<l;)
			_add(a[--l]);
		for (;q[i].l>l;)
			_del(a[l++]);
		for (;q[i].r<r;)
			_del(a[r--]);
		for (;q[i].r>r;)
			_add(a[++r]);
		if (q[i].t==1)
			ans[q[i].i]=(s1&(s1<<q[i].k)).any();
		else if (q[i].t==2)
			ans[q[i].i]=(s1&(s2>>(MAXN-q[i].k))).any();
		else
		{
			for (int j=1;j*j<=q[i].k && !ans[q[i].i];j++)
				if (!(q[i].k%j) && s1[j] && s1[q[i].k/j])
					ans[q[i].i]=1;
		}
	}
	for (int i=0;i<m;i++)
		printf("%s\n",ans[i]?"hana":"bi");
	return 0;
}