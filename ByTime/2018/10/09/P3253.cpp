#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tnode {int v,i;};

Tnode t[MAXN];
int a[MAXN],b[MAXN];
int n,m;
long long ans=0ll;

void solve() {
	
}
inline void _add(int x,int v)
{
	for (int i=x;i<=n+m;i+=i&(-i))
		b[i]+=v;
	return ;
}
inline long long _query(int x)
{
	long long ans=0ll;
	for (int i=x;i;i-=i&(-i))
		ans+=1ll*b[i];
	return ans;
}

bool _cmp(Tnode a,Tnode b) {return a.v>b.v;}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=n;i;i--)
		scanf("%d",&a[i]);
	for (int i = n + 1; i <=n+m;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n+m;i++)
		t[i].v=a[i],t[i].i=i,_add(i,1);
	sort(t+1,t+1+n+m,_cmp);
	int j,p=n;
	for (int i=1;i<=n+m;i++)
	{
		j=t[i].i;
		if (p>=j)
		{
			ans+=_query(p);
			ans-=_query(j);
			p=j;
			_add(j,-1);
		}
		else
		{
			ans+=_query(--j);
			ans-=_query(p);
			p=j;
			_add(j+1,-1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}