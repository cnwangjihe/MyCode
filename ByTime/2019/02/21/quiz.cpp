// Date      : 2019-02-21 08:11:33
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXL = 509,
		  MAXN = 7009;

struct BigInt
{
	int v[MAXL],len,k;
	BigInt(int _k=10) {k=_k;memset(v,0,sizeof v);len=0;}
	BigInt& operator= (int a) {for (len=0;a;v[len++]=a%k,a/=k);return *this;}
	BigInt operator* (const BigInt& a)
	{
		if (k!=a.k)
			exit(19260817);
		BigInt ans(k);
		ans.len=min(MAXL,len+a.len);
		for (int i=0;i<len;i++)
			for (int j=0;j<a.len;j++)
			{
				if (i+j>=MAXL)
					break;
				ans.v[i+j]+=v[i]*a.v[j];
			}
		for (int i=0;i<ans.len && i+1<MAXL;i++)
			ans.v[i+1]+=(ans.v[i]/k),ans.v[i]%=k;
		while (ans.len && (!ans.v[ans.len-1]))
			ans.len--;
		return ans;
	}
	BigInt operator+ (BigInt a)
	{
		BigInt ans(k);
		ans.len=min(MAXL,max(len,a.len)+1);
		for (int i=0;i<ans.len;i++)
			ans.v[i]=v[i]+a.v[i];
		for (int i=0;i<ans.len && i+1<MAXL;i++)
			ans.v[i+1]+=(ans.v[i]/k),ans.v[i]%=k;
		while (ans.len && (!ans.v[ans.len-1]))
			ans.len--;
		return ans;
	}
	void Print()
	{
		for (int i=len-1;~i;i--)
			putchar(v[i]+'0');
		putchar('\n');
		return ;
	}
};

bool Check(pair<BigInt,BigInt> p,int n)
{
	if (p.first.k!=2 || p.second.k!=10)
		return 0;
	for (int i=0;i<n;i++)
		if ((i<p.first.len?p.first.v[i]:0)!=(i<p.second.len?p.second.v[i]:0))
			return 0;
	return 1;
}

int n;
BigInt t2(2),k2(2),t10(10),k10(10);
pair<BigInt,BigInt> q[2][2][MAXN];
int cnt[2][2];

int main()
{
	freopen("quiz.in","r",stdin);
	freopen("quiz.out","w",stdout);
	scanf("%d",&n);
	t2=10,t10=10;
	k2=1,k10=1;
	pair<BigInt,BigInt> tmp;
	q[0][0][cnt[0][0]++]=make_pair(BigInt(2),BigInt(10));
	for (int i=1,now=0,nxt=1;;i++,now^=1,nxt^=1,k2=k2*t2,k10=k10*t10)
	{
		cnt[0][nxt]=cnt[1][nxt]=0;
		for (int g=0;g<2;g++)
			for (int j=0;j<cnt[g][now];j++)
			{
				tmp=q[g][now][j];
				if (Check(tmp,i))
					q[0][nxt][cnt[0][nxt]++]=tmp;
				tmp.first=tmp.first+k2;
				tmp.second=tmp.second+k10;
				if (Check(tmp,i))
				{
					if (!(--n))
						return tmp.second.Print(),0;
					q[1][nxt][cnt[1][nxt]++]=tmp;
				}
			}
	}
	return 0;
}