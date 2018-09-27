#include <bits/stdc++.h>
using namespace std;

const int mx=5e5+10;

int n,a[mx],b[mx],c[mx];
int cnt[mx],cs[mx];

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

void solve1()
{
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int pos=1;
	for(int i=1;i<=n;i++)
		while(a[pos]<=b[i] && pos<=n) cnt[pos]=i-1,pos++;
	while(pos<=n) cnt[pos]=n,pos++;

	int ans=0;
	for(int i=1;i<=n;i++)
		cs[cnt[i]]++;
	for(int i=1;i<=n;i++)
		ans=min(ans+cs[i],i);
	
	printf("%d\n",ans);
}

int ch[mx];
int da[mx],db[mx],m=0;

void solve2()
{
}

int main()
{
//	freopen("b.in","r",stdin);
//	freopen("b.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)
		c[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=n;i++)
		a[i]=read();


	bool fl=0;
	for(int i=1;i<=n;i++)
		if(c[i]!=1) fl=1;

	if(!fl) solve1();
	else solve2();
	
	
	return 0;
}
