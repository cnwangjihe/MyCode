#include<bits/stdc++.h>
#define sec second
#define mkp make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;

const int maxn = 5e4 + 10;

int n,m,a[maxn];
map<int,int> mp;
ll sum;

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+(c^48);
	return x;
}
inline void op(int l,int r)
{
	printf("%d %d\n",l,r);
	sum+=r-l+1;
	reverse(a+l,a+r+1);
}

void input()
{
	int i;
	
	n=read();
	for(i=1;i<=n;i++) a[i]=read(),mp[a[i]]=0;
	m=0;
	for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++) it->sec=m++;
	for(i=1;i<=n;i++) a[i]=mp[a[i]];
}

int c[maxn],b[maxn];
void div(int l,int r,int al,int ar)
{
	if(r<=l || al==ar) return;
	
	int i,L=l,R=r,amid=al+ar>>1,cnt;
	
	while(L<=R)
	{
		for(;a[L]<=amid;L++);
		for(;a[R]>amid;R--);//printf("L=%d R=%d ",L,R);
		
		c[0]=1;b[0]=L;cnt=1;
		for(i=L+1;i<=R;i++)
		{
			if((a[i]<=amid)!=(a[i-1]<=amid)) 
			{
				c[cnt]=1^c[cnt-1];b[cnt]=i;
				cnt++;
			}
		}
		b[cnt]=R+1;
		
		int mx=0,mxi=-1;
		for(i=0;i<cnt;i++) if(mx<b[i+1]-b[i]) mx=b[i+1]-b[i],mxi=i;
		if(!~mxi) break;
		if(c[mxi]) op(b[mxi],R);
		else     op(L,b[mxi+1]-1);
	}
	
	div(l,R,al,amid);
	div(L,r,amid+1,ar);
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("#3.out","w",stdout);
	
	input();
	div(1,n,0,m-1);
	printf("-1 -1\n");
	//cerr<<sum;
	
	return 0;
}