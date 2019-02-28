// Date      : 2019-02-19 19:40:29
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P3649
// Algorithm : PalindromicTree
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 300009,
		  MAXS = 27;

struct PalindromicTree
{
	struct Tnode
	{
		int fail,next[MAXS],len,cnt;
		inline void reset(int _len=0,int _fail=0,int _cnt=0) {cnt=_cnt,fail=_fail,len=_len;memset(next,0,sizeof next);}
	};
	int last,fp,n;
	Tnode t[MAXN];
	int s[MAXN];
	PalindromicTree()
	{
		fp=2,last=1,n=0;
		t[1].reset(-1);
		t[0].reset(0,1);
	}
	int GetFail(int u,int i)
	{
		while (s[i-t[u].len-1]!=s[i])
			u=t[u].fail;
		return u;
	}
	void Add(int c)
	{
		int u;
		s[n++]=c;
		last=GetFail(last,n-1);
		if (!t[last].next[c])
		{
			u=fp++;
			t[u].reset(t[last].len+2,t[GetFail(t[last].fail,n-1)].next[c],0);
			t[last].next[c]=u;
		}
		t[last=t[last].next[c]].cnt++;
	//	cerr << last << ' ' << t[last].fail << ' ' << t[last].cnt << ' ' << t[last].len << '\n';
		return ;
	}
	long long Query()
	{
		long long ans=0;
		for (int u=fp-1;u>1;u--)
		{
			t[t[u].fail].cnt+=t[u].cnt;
			ans=max(ans,1ll*t[u].len*t[u].cnt);
		}
		return ans;
	}
};

PalindromicTree PT;

int main()
{
//	freopen("P3649.in","r",stdin);
//	freopen("P3649.out","w",stdout);
	char c;
	do {c=getchar();}
		while (c<'a' || c>'z');
	do
	{
		PT.Add(c-'a'+1);
		c=getchar();
	}while (c>='a' && c<='z');
	printf("%lld\n",PT.Query());
	return 0;
}