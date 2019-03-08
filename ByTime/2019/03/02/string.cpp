// Date      : 2019-03-02 09:19:43
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 4009,
		  MOD  = 1000000007;

int nxt[MAXN][MAXN],dep[MAXN][MAXN];
int s[MAXN],k[MAXN];
int n,ans=0;

int Add(int i)
{
	int ans=0;
	for (int j=0;j<i;j++)
	{
		while (k[j]>=0 && s[i]!=s[k[j]+1+j])
			k[j]=nxt[j][k[j]];
		if (s[i]==s[k[j]+1+j])
			k[j]++;
		nxt[j][i-j]=k[j];
		dep[j][i-j]=(~nxt[j][i-j])?dep[j][nxt[j][i-j]]+1:0;
		(ans+=dep[j][i-j])%=MOD;
	}
	nxt[i][0]=-1;
	k[i]=-1;
	dep[i][0]=0;
	return ans;
}

int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d",&n);n=0;
	do {s[0]=getchar()-'a'+1;}
		while (s[0]<1 || s[0]>26);
	do {s[++n]=getchar()-'a'+1;}
		while (s[n]>0 && s[n]<27);
	int now=0,last=0;
	for (int i=0;i<n;i++)
	{
		now=Add(i);
		(last+=now)%=MOD;
		(ans+=last)%=MOD;
		printf("%d\n",ans);
	}
	return 0;
}