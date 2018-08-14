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
	bool flag=0;
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)
		line[tail++]=i,_in[i]=1;
	for (int i=n-m+1;i;i--)
	{
		if (flag)
		{
			if (w[1]<a[i])
				flag=0;
			for (int j=0;j<k && flag;j++)
				if (w[fix[j]]<w[i+fix[j]-1])
					flag=0;
			ans+=flag;
		}
		else
		{
			flag=1;
			for (int j=1;j<=m && flag;j++)
				if (w[j]<a[i+j-1])
					flag=0;
			ans+=flag;
		}
	}
//	cerr << cnt << "    ";
	printf("%d\n",ans);
	return 0;
}