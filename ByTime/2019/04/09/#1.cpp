#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
const int N=1e6+10;

int n,a[N],m,cnt[35],cot,ans;
int bn[35],mst[35];

char cp,buf[N],wbuf[N],os[100];
int p1,p2,p3;
inline char gc(){
	if(p1==p2) p1=0,p2=fread(buf,1,N,stdin);
	return p1==p2?EOF:buf[p1++];
}

inline void rd(int &x)
{
	cp=getchar();x=0;
	for(;!isdigit(cp);cp=getchar());
	for(;isdigit(cp);cp=getchar()) x=x*10+(cp^48);
}

inline void wchar(char x)
{
	if(p3==N) fwrite(wbuf,1,N,stdout),p3=0;
	wbuf[p3++]=x;
}

inline int fd(int x)
{
	if(!x) return -1;
	int l=0,r=30,mid,y;
	for(;l<=r;){mid=(l+r)>>1;(x>=(1<<mid))?(l=(y=mid)+1):(r=mid-1);}
	return y;
}

void chg(int x,int y,int op)
{
	x=fd(x);if(x==-1) return;
	if(op){
		if((a[y]>>x)&1) bn[x]++;else{mst[x]++;ans|=(1<<x);}
	}else{
		if((a[y]>>x)&1) bn[x]--;else{mst[x]--;if((!mst[x])) ans^=(1<<x);}
	}
	
}

inline void prit()
{
	int i;
	for(i=0;i<=30;++i) if((bn[i] && mst[i])) break;
	if(i<=30){
	  wchar('-');wchar('1');
	}
	else{
		int x=ans,re=0;
		for(;(!re)||(x);x/=10) os[++re]='0'+(x%10);
		for(;re;--re) wchar(os[re]);
	}
	if(m>1) wchar('\n');
}

int main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	int i,x,y,l,r,mid;
	rd(n);for(i=1;i<=n;++i) rd(a[i]);
	for(i=2;i<=n;++i) chg(a[i-1]^a[i],i,1);
	for (int i=0;i<=30;i++)
		cerr << bn[i] << ' ' << mst[i] << '\n';
	return 0;
	rd(m);m++;prit();m--;
	for(;m;--m){
		rd(x);rd(y);
		if(x>1) chg(a[x]^a[x-1],x,0);
		if(x<n) chg(a[x]^a[x+1],x+1,0);
		a[x]=y;
		if(x>1) chg(a[x]^a[x-1],x,1);
		if(x<n) chg(a[x]^a[x+1],x+1,1);
		prit();
	}
	if(p3) fwrite(wbuf,1,p3,stdout);
	fclose(stdin);fclose(stdout);
	return 0;
}