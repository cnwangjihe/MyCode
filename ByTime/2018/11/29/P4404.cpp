// Date    : 2018-11-29 15:33:56
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000009;

priority_queue<pair<int,int> > q;
int n,m,k=0,ans=0,cnt=0;
int a[MAXN],b[MAXN],nxt[MAXN];
int p[MAXN];
bool _in[MAXN];

bool _cmp(int A,int B){return a[A]<a[B];}

int main()
{
//	freopen("P4404.in","r",stdin);
//	freopen("P4404.out","w",stdout);
	
	memset(_in,0,sizeof _in);
	memset(nxt,127,sizeof nxt);

	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]),p[i]=i;
	sort(p,p+n,_cmp);
	for (int i=0;i<n;i++)
	{
		while (i+1<n && a[p[i]]==a[p[i+1]])
			a[p[i]]=cnt,i++;
		a[p[i]]=cnt++;
	}

//	cerr << "&&";
	for (int i=n-1;~i;i--)
		b[i]=nxt[a[i]],nxt[a[i]]=i;
	for (int i=0;i<n;i++)
	{
//		cerr << i << " : " << a[i] << '\n';
		if (!_in[a[i]])
		{
			while (k>=m)
			{
				_in[q.top().second]=0;
//				cerr << "  " << q.top().second << " " << q.top().first << '\n';
				q.pop();
				k--;
			}
			q.push(make_pair(b[i],a[i]));
			_in[a[i]]=1;
			k++;
			ans++;
		}
		else
			q.push(make_pair(b[i],a[i]));
	}
	printf("%d\n",ans);

	return 0;
}