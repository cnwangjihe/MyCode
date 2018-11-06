#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tpoint
{
	map<int,int> cnt;
	int i,nxt,ans;
};

Tpoint p[MAXN];
int a[MAXN];
int n,sum,ctim=0;

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
	freopen("2703.in","r",stdin);
	freopen("2703.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=n;i++)
	{
		p[i].i=i;
		p[i].nxt=i+1;
		p[i].cnt[a[i]]++;
		p[i].ans=1;
	}
	p[n].nxt=-1;
	int v,i,j,u;
	for (i=1;i<=n;i++)
	{
		sum=0;
		for (u=1;~u;u=p[u].nxt)
		{
			sum++;
			for (j=p[u].i+1;j<=n;j++)
			{
				v=p[u].nxt;
				if (p[u].cnt[a[j]]==0)
				{
					if (p[u].ans+1>i)
						break;
					p[u].ans++;
					p[u].cnt[a[j]]++;
					p[u].i=j;
					if (~v)
					{
						if (p[u].i>=p[v].i)
							p[u].nxt=p[v].nxt;
						else 
						{
							p[v].cnt[a[j]]--;
							if (!p[v].cnt[a[j]])
								p[v].ans--;
						}
					}
				}
				else
				{
					p[u].cnt[a[j]]++;
					p[u].i=j;
					if (~v)
					{
						if (p[u].i>=p[v].i)
							p[u].nxt=p[v].nxt;
						else
						{
							p[v].cnt[a[j]]--;
							if (!p[v].cnt[a[j]])
								p[v].ans--;
						}
					}
				}
			}
		}
		printf("%d ",sum);
	}
//	cerr << "\n!! ctim: " << ctim << endl;
//	for (;;);
	return 0;
}