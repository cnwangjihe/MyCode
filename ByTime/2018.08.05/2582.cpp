#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009;
const bool RIGHT = 1,
		   LEFT  = 0;

struct Tnode
{
	int c[2],size[2];
	void reset() {c[0]=c[1]=-1;size[0]=size[1]=0;}
	Tnode(){reset();}
};

Tnode t[MAXN*31];
long long f[2][33];
long long ans;
int a[MAXN];
int n,fp=1;

void modify(int k,int u,int v,int d,int val)
{
	t[u].size[k]+=val;
//	cerr << t[u].size[k];
	if (d==-1)
		return ;
	int ch=((v&(1<<d))!=0);
	if (t[u].c[ch]==-1)
	{
		t[u].c[ch]=fp;
		t[fp].reset();
		fp++;
	}
	f[k^ch][d]-=(long long)t[t[u].c[0]].size[k^ch]*t[t[u].c[1]].size[k^ch^1];
	modify(k,t[u].c[ch],v,d-1,val);
	f[k^ch][d]+=(long long)t[t[u].c[0]].size[k^ch]*t[t[u].c[1]].size[k^ch^1];
	return ;
}

int main()
{
	freopen("2582.in","r",stdin);
	freopen("2582.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		fp=1;
		ans=0;
		scanf("%d",&n);
		t[0].reset();
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=3;i<=n;i++)
			modify(RIGHT,0,a[i],31,1);//,cerr << "ddd \n";
		for (int i=2;i<n;i++)
		{
			modify(LEFT,0,a[i-1],31,1);
		//	cerr << '\n';
			for (int j=0;j<=31;j++)
				ans+=f[(a[i]&(1<<j))!=0][j];
			modify(RIGHT,0,a[i+1],31,-1);
		//	cerr << '\n';
		}
		printf("%lld\n",ans);
	}
	return 0;
}