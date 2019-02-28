#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;

int conb[52][52];
int f[27][27][27][27][52];
int g[27][27][52];
int h[27][27][52];
int n,R,G,B;

inline void MODR(int &a,int x){a+=x;if(a>=mod) a-=mod;}
inline int MOD(int x){return x<mod?x:x-mod;}
inline ll C(int n,int r)
{
	if(r<0||r>n) return 0;
	if(!r||r==n) return 1;
	if(conb[n][r]) return conb[n][r];
	return conb[n][r]=MOD(C(n-1,r-1)+C(n-1,r));
}

void dp1()
{
	int i,mh,h,b,r,t;

	//memset(f,0,sizeof(f));

	f[0][0][0][0][0]=1;
	for(i=0;i<26;i++)
	{
		for(mh=0;mh<26;mh++) for(h=0;h<=mh;h++) 
		{
			for(b=0;b<26;b++) for(r=0;r<51;r++) if((t=f[i][h][mh][b][r]))
			{
				if(!h) MODR(g[i][b][r],t);
				MODR(f[i][h+1][max(h+1,mh)][b+1][r],t);
				if(h<mh) MODR(f[i][h+1][mh][b][r+1],t);
				MODR(f[i+1][0][mh][b][r],t);
			}
		}
	}
}

ll dp2(int B,int R)
{
	int i,b,r,cb,cr,t;
	cerr << f[n][1][1][2][0] << '\n';
	memset(h,0,sizeof(h));h[0][0][0]=1;
	for(i=0;i<n;i++) for(b=0;b<=B;b++) for(r=0;r<=R;r++) if((t=h[i][b][r]))
	{
		for(cb=0;cb+b<=B;cb++) for(cr=0;cr+r<=R;cr++)
			MODR(h[i+1][cb+b][cr+r],(ll)h[i][b][r]*g[n][cb][cr]%mod);
	}
	//cerr<<n<<' '<<B<<' '<<R<<endl;
	return h[n][B][R];
}

int main()
{
	int T;
	dp1();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&R,&G,&B,&n);
		cerr << dp2(R,G+B) << '\n';
		printf("%lld\n",(dp2(R,G+B)*C(G+B,G)+dp2(G,B+R)*C(B+R,B)+dp2(B,R+G)*C(R+G,R))%mod);
	}
	
	return 0;
}