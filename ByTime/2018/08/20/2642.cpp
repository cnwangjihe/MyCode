#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int fa[MAXN],fas[MAXN],son[MAXN];
map<string,int> mp1,mp2;
vector<char> p[MAXN];
int fp1=1,fp2=1;
string s[MAXN];
int ans=1;
int n;

int main()
{
	freopen("2642.in","r",stdin);
	freopen("2642.out","w",stdout);
	int t,x;
	char c;
	string tmp;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&t,&x);
		do {c=getchar();}
			while (c<'a' || c>'z');
		if (t==1)
		{
			s[++fp1]=s[x]+c;
			mp1[s[fp1]]++;
			ans+=mp2[s[fp1]];
		}
		else
		{
			p[x].push_back(c);
			fa[++fp2]=x;
			fas[fp2]=son[x];
			son[x]++;
			tmp="";
			for (int u=fp2;fa[u];u=fa[u])
			{
				tmp=tmp+p[fa[u]][fas[u]];
				mp2[tmp]++;
				ans+=mp1[tmp];
			}
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
