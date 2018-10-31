#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int mod=1e9+7;
const int mxn=505;
int n,k;
int f[2][mxn][(1<<11)];
int p[mxn],plen=0;

int sep(int x,int len)
{
	int tmp=0;
	for(int i=0;i<len;i++)
		tmp|=((x%p[i]==0)<<i);
	for(int i=0;i<len;i++)
		if(x%(p[i]*p[i])==0) return -1;
	
	return tmp;
}

void solve1()
{
	int len=0;
	for(;len<=10 && p[len]<=n;len++);
	
	memset(f,0,sizeof f);
		
	cerr<<len<<"###\n";
	
	int full=(1<<len)-1;
	f[1][0][0]=1;
	int cnt=0;
	for(int i=2;i<=n;i++)
	{
		int x=i&1,y=x^1;
		int tmp=sep(i,len);
//		cerr<<i<<": "<<tmp<<endl;
		if(tmp!=-1) cnt++;
		for(int j=0;j<=min(k,cnt);j++)
			for(int s=0;s<=full;s++)
			{
				(f[x][j][s]+=f[y][j][s])%=mod;
				if(tmp!=-1 && j && ((s&tmp)==tmp)) (f[x][j][s]+=f[y][j-1][s-tmp])%=mod;
			}
		for(int j=0;j<=k;j++)
			for(int s=0;s<=full;s++)
				f[y][j][s]=0;

/*		for(int j=0;j<=min(k,cnt);j++)
		{
			int tmp=0;
			for(int s=0;s<=full;s++)
				tmp+=f[x][j][s];
			cerr<<tmp<<" ";
		}
		cerr<<endl;
*/	}

	int ans=0;
	for(int j=0;j<k;j++)
		for(int s=0;s<=full;s++)
			(ans+=f[n&1][j][s])%=mod;
	ans=(ans*2)%mod;
	for(int s=0;s<=full;s++)
		(ans+=f[n&1][k][s])%=mod;
		
	ans=(ans-1+mod)%mod;
	printf("%d\n",ans);
}

void solve()
{
	scanf("%d%d",&n,&k);
	if(n<=30)
	{
		solve1();
		return ;
	}
	
}

int main()
{
//	freopen("mul.in","r",stdin);
//	freopen("mul.out","w",stdout);
	
	for(int i=2;i<=500;i++)
	{
		bool fl=0;
		for(int j=2;j*j<=i;j++)
			if(i%j==0)
			{
				fl=1;
				break;
			}
		if(!fl) p[plen++]=i;
	}
	
	int t;
	scanf("%d",&t);
	while(t>0)
	{
		t--;
		solve();
	}	
	
	
	return 0;
}
