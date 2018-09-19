#include<bits/stdc++.h>
#define get(x) __builtin_popcount(x)
using namespace std;

const int mod=1e9+7,N=1<<11;
int T,n,m,S;
int ans[12],f[N];

void up(int &x,int y){x+=y;if(x>=mod)x-=mod;if(x<0)x+=mod;}

int main()
{
	freopen("2654.in","r",stdin);
	freopen("2654.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));f[0]=1;
		scanf("%d%d",&n,&m);S=1<<n;
		while(m--)
		{
			char opt[2];int u,v;
			scanf("%s%d%d",opt,&u,&v);--u;--v;
			int tmp=(1<<u)|(1<<v);
			if(opt[0]=='+')
				{for(int i=S-1;~i;--i) if(!(tmp&i)) up(f[i^tmp],f[i]);}
			else
				{for(int i=0;i<S;++i) if(!(tmp&i)) up(f[i^tmp],-f[i]);}
			memset(ans,0,sizeof(ans));
			for(int i=1;i<S;++i) up(ans[get(i)],f[i]);
			for(int i=2;i<=n;i+=2) {if(i^2) putchar(' ');printf("%d",ans[i]);} puts("");
		}
	}
	
	return 0;
}