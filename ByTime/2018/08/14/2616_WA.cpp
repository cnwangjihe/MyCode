#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300009;

int w[MAXN],a[MAXN];
int fix[MAXN],line[MAXN];
int n,m,step,MOD,k=0;
bool _in[MAXN];
int ans=0,cnt=0;
int head=0,tail=0;

int main()
{
	freopen("2616.in","r",stdin);
	freopen("2616.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&w[1],&step,&MOD);
	for (int i=2;i<=m;i++)
	{
		w[i]=(w[i-1]+step)%MOD;
		if (w[i]<w[i-1])
			fix[k++]=i;
	}
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if (MOD<=1000)
	{
		for (int i=1;i+m-1<=n;i++)
		{
			bool f=1;
			for (int j=1;j<=m && f;j++)
				if (w[j]<a[i+j-1])
					f=0;
			if (f)
				ans++;
		}
		printf("%d\n",ans);
		return 0;
	}
	else
	{
		for (int i=1;i<=m;i++)
			line[tail++]=i,_in[i]=1;
		for (int i=n-m+1;i;i--)
		{
			for (int j=0;j<k;j++)
				if (!_in[fix[j]])
					line[tail++]=fix[j],tail%=MAXN,_in[fix[j]]=1;
			if (!_in[1])
				line[tail++]=1,tail%=MAXN,_in[1]=1;
			int j,ta=tail;
			while (head!=ta)
			{
				j=line[head];
			//	cerr << j << ' ' << i+j-1 << '\n';
			//	cnt++;
				_in[j]=0;
				if (w[j]<a[i+j-1])
				{
					line[tail++]=j;
					tail%=MAXN;
					_in[j]=1;
					if (j+1<=m && !_in[j+1])
					{
						line[tail++]=j+1;
						tail%=MAXN;
						_in[j+1]=1;
					}
				//	break;
				}
				head++;
				head%=MAXN;
			}
			if (head==tail)
				ans++;
		}
	//	cerr << cnt << "    ";
		printf("%d\n",ans);
		return 0;
	}
	return 0;
}