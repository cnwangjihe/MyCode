#include<bits/stdc++.h>

using namespace std ;

const int inf=1e9+10,N=1e5+10;

int n,k,m,s;
int ban[N],f[N],lst[2];
priority_queue<int,vector<int>,greater<int> >q[2],p[2];

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&k,&m,&s);
	for (int i=1;i<=m;i++) scanf("%d",ban+i);
	sort(ban+1,ban+m+1);
//	for (int i=1;i<=m;i++) cout<<ban[i]<<" ";cout<<endl;
	for (int i=0;i<=n+5;i++) f[i]=inf;
	int banpos=1,o;f[s]=0;
	q[0].push(inf);lst[0]=0;
	q[1].push(inf);lst[1]=1;
	for (int i=1;i<=n;i++)
	{
		if (i==ban[banpos])
		{
			banpos++;
			continue;
		}
		o=(i&1)^(k&1)^1;
//	cout<<"i="<<i<<endl;
//	cout<<q[o].top()+1<<" "<<f[i]<<endl;
//	cout<<"last="<<lst[o]<<endl;
//	cout<<endl;
		f[i]=min(q[o].top()+1,f[i]);
		q[i&1].push(f[i]);
		if (i-(k-1)==lst[o])
		{
			p[o].push(f[lst[o]]);
			lst[o]+=2;
			while (!q[o].empty()&&!p[o].empty())
			{
				if (q[o].top()==p[o].top())
				{
					q[o].pop();p[o].pop();
				}
				else break;
			}
		}
	}
	
	while (!q[0].empty()) q[0].pop();
	while (!q[1].empty()) q[1].pop();
	while (!p[0].empty()) p[0].pop();
	while (!p[1].empty()) p[1].pop();
	
	banpos=m;
	q[0].push(inf);lst[0]=(n>>1)<<1;
	q[1].push(inf);lst[1]=(n>>1)<<1|1;
	for (int i=n;i>=1;i--)
	{
		if (i==ban[banpos])
		{
			banpos--;
			continue;
		}
		o=(i&1)^(k&1)^1;
		f[i]=min(q[o].top()+1,f[i]);
		q[i&1].push(f[i]);
		if (i-(k-1)==lst[o])
		{
			p[o].push(f[lst[o]]);
			lst[o]+=2;
			while (!q[o].empty()&&!p[o].empty())
			{
				if (q[o].top()==p[o].top())
				{
					q[o].pop();p[o].pop();
				}
				else break;
			}
		}
	}
	
	for (int i=1;i<=n;i++)
		if (f[i]==inf) printf("-1 ");
		else printf("%d ",f[i]);
	puts("");
	
	return 0;
}
