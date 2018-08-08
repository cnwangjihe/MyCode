#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e+5 + 10;

int n,k;
char s[maxn];
int ox[maxn],oy[maxn],sa[maxn],cnt[maxn],hi[maxn],*x=ox,*y=oy;

struct tree{
	int a[maxn];
	void add(int x){for(x++;x<maxn;x+=x&-x) a[x]++;}
	int sum(int x){int ans=0;for(x++;x>0;x-=x&-x) ans+=a[x];return ans;}
}T;

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	return x;
}

void input()
{
	scanf("%d%d%s",&n,&k,s);
}

bool same(int *r,int a,int b,int len)
{
	if((a+len<n)!=(b+len<n) || r[a]!=r[b]) return false;
	return ((a+len<n)?(r[a+len]==r[b+len]):true); 
}
void suffix()
{
	int i,j,t,m=26,len;
	
	for(i=0;i<m;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[x[i]=s[i]-'a']++;
	for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for(i=0;i<n;i++) sa[ --cnt[x[i]] ]=i;
	for(len=1;len==1||m<n;len<<=1)
	{
		t=0;
		for(i=n-len;i<n;i++) y[t++]=i;
		for(i=0;i<n;i++) if(sa[i]>=len) y[t++]=sa[i]-len;
		for(i=0;i<m;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[ x[y[i]] ]++;
		for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[ --cnt[x[y[i]]] ]=y[i];
		m=1;swap(x,y);x[sa[0]]=0;
		for(i=1;i<n;i++) x[sa[i]] = same(y,sa[i-1],sa[i],len)?m-1:m++;
		
	}
	
	t=0;
	for(i=0;i<n;i++)
	{
		if(t) t--;
		if(!x[i]) continue;
		j=sa[x[i]-1];
		while(i+t<n && j+t<n && s[i+t]==s[j+t]) t++;
		hi[x[i]]=t;
	}
}

void solve()
{
	int i,j;
	int ans=0;
	
	for  (int i=0;i<n;i++)
		cerr << sa[i] << ' ' << x[i] << '\n';
	for(i=1;i<n;i=j+1)
	{
		for(j=i;hi[j]>=k && j<n;j++);
		sort(sa+i-1,sa+j);
	}
	for(i=0;i<n;i++)
	{//cout<<sa[i]<<endl;
		ans+=i-T.sum(sa[i]);
		T.add(sa[i]);
	}//cerr<<"RUN";
	
	cout<<ans;
}

int main()
{
//	freopen("2464.in","r",stdin);
//	freopen("2464.out","w",stdout);
	
	input();
	suffix();
	solve();
	
	return 0;
}
