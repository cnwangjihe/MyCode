#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 500010
char A[MAXN],ans[MAXN];
int N,T,K;
namespace SAM
{
	int son[MAXN<<1][27],par[MAXN<<1],len[MAXN<<1],root,last,sz,size[MAXN<<1];
	inline void Init() {root=sz=last=1;}
	inline void Extend(int c)
	{
		int cur=++sz,p=last;
		len[cur]=len[p]+1; size[cur]=1;
		while (p && !son[p][c]) son[p][c]=cur,p=par[p];
		if (!p) par[cur]=root;
		else
			{
				int q=son[p][c];
				if (len[p]+1==len[q]) par[cur]=q;
				else
					{
						int nq=++sz;
						memcpy(son[nq],son[q],sizeof(son[nq]));
 
						len[nq]=len[p]+1;
						par[nq]=par[q];
						while (p && son[p][c]==q) son[p][c]=nq,p=par[p];
						par[cur]=par[q]=nq;
					}
			}
		last=cur;
	}
	inline void Build() {Init(); for (int i=1; i<=N; i++) Extend(A[i]-'a'+1);}
	int st[MAXN],id[MAXN<<1],sum[MAXN<<1];
	inline void Pre()
	{
		for (int i=1; i<=sz; i++) st[len[i]]++;
		for (int i=1; i<=N; i++) st[i]+=st[i-1];
		for (int i=1; i<=sz; i++) id[st[len[i]]--]=i;
		if (!T)
			{
				for (int i=sz; i>=1; i--) size[i]=1;
				size[root]=0;
				for (int i=sz,Sum=0; i>=1; i--,Sum=0)
					{
						for (int j=1; j<=26; j++)
							Sum+=sum[son[id[i]][j]];
						sum[id[i]]=Sum+1;
					}
			}
		else
			{
				for (int i=sz; i>=1; i--)
					size[par[id[i]]]+=size[id[i]];
				size[root]=0;
				for (int i=sz; i>=1; i--)
					{
						sum[id[i]]=size[id[i]];
						for (int j=1; j<=26; j++)
							sum[id[i]]+=sum[son[id[i]][j]];
					}
			}
	}
	inline void Query(int K)
	{
		int now=root,tot=0;
		while (K)
			{
				for (int i=1; i<=26; i++)
					if (son[now][i])
						if (sum[son[now][i]]>=K)
							{
								ans[++tot]='a'+i-1;
								K-=size[son[now][i]];
								now=son[now][i];
								break;
							}
						else K-=sum[son[now][i]];
 
			}
		ans[++tot]=0;
	}
}using namespace SAM;
int main()
{
	scanf("%s",A+1);
	N=strlen(A+1);
	SAM::Build();
	scanf("%d%d",&T,&K);
	SAM::Pre();
	if (sum[root]<=K)
		puts("-1");
	else
		Query(K),puts(ans+1);
	return 0;
}
