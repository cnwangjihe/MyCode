// Date      : 2019-03-12 21:20:10
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : SAM,TopoSort
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const pair<int,int> NDAG = make_pair(-1,-1); 
const int MAXN = 1000009,
		  MAXM = MAXN*5,
		  MAXC = 27;

struct SAM
{
	int C[MAXN*2][MAXC];
	int link[MAXN*2],len[MAXN*2];
	int fp;
	SAM() {memset(C,-1,sizeof C);memset(link,-1,sizeof link),fp=1;}
	inline void Copy(int a,int b)
	{
		for (int i=0;i<26;i++)
			C[a][i]=C[b][i];
		link[a]=link[b];
	}
	int Extend(int last,int c)
	{
		int cur=fp++,p;
		len[cur]=len[last]+1;
		for (p=last;p!=-1 && C[p][c]==-1;p=link[p])
			C[p][c]=cur;
		if (p==-1)
		{
			link[cur]=0;
			return cur;
		}
		int q=C[p][c];
		if (len[q]==len[p]+1)
		{
			link[cur]=q;
			return cur;
		}
		int clone=fp++;
		Copy(clone,q);
		len[clone]=len[p]+1;
		link[q]=clone;
		link[cur]=clone;
		for (;~p && C[p][c]==q;p=link[p])
			C[p][c]=clone;
		return cur;
	}
};

SAM SAM;
int _head[MAXN*4],_node[MAXM],_val[MAXM],_next[MAXM];
int cnt[MAXN*4];
pair<int,int> str[MAXN*2];
stack<int> fail[MAXC];
queue<int> q;
int d[MAXN*4],f[MAXN*4],w[MAXN*4];
int m[MAXN],ans[MAXN];
vector<int> s[MAXN];
int n,k,fp=0;

inline void _connect(int a,int b,int v=0)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void Insert(const vector<int>& s,int n,int pos)
{
	int cur=0;
	for (int i=0;i<n;i++)
	{
		cur=SAM.Extend(cur,s[i]);
		str[cur]=make_pair(pos,i);
	}
	return ;
}

void BuildTree()
{
	for (int i=1;i<SAM.fp;i++)
	{
		_connect(SAM.link[i],i);
	}
	return ;
}

void Dfs(int u)
{
	int v;
	if (SAM.len[u]>=k)
	{
		for (int i=0;i<26;i++)
			if (~SAM.C[u][i])
			{
				v=SAM.C[u][i];
				if (SAM.len[v]>=k)
					_connect(u+SAM.fp,v+SAM.fp,i),cnt[v+SAM.fp]++;
			}
			else if (fail[i].size())
				_connect(u+SAM.fp,fail[i].top()+SAM.fp,i),cnt[fail[i].top()+SAM.fp]++;
	}
	if (SAM.len[u]+1>=k)
		for (int i=0;i<26;i++)
			if (~SAM.C[u][i])
				fail[i].push(SAM.C[u][i]);
	for (int i=_head[u];~i;i=_next[i])
		Dfs(_node[i]);
	if (SAM.len[u]+1>=k)
		for (int i=0;i<26;i++)
			if (~SAM.C[u][i])
				fail[i].pop();
	return ;
}

void Solve()
{
	memset(d,0,sizeof d);
	memset(f,0,sizeof f);
	for (int i=SAM.fp;i<2*SAM.fp;i++)
	{
		if (!cnt[i])
			q.push(i);
		d[i]=str[i-SAM.fp].second+1;
	}
	int vis=0,u,v;
	while (!q.empty())
	{
		u=q.front();q.pop();
		vis++;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (d[v]<d[u]+1)
				d[v]=d[u]+1,f[v]=u,w[v]=_val[i];
			if (!--cnt[v])
				q.push(v);
		}
	}
	if (vis!=SAM.fp)
		return (void)printf("INF\n");
	u=SAM.fp;
	for (int i=SAM.fp+1;i<2*SAM.fp;i++)
		if (d[u]<d[i])
			u=i;
	int len=0;
	for (;f[u];u=f[u])
		ans[len++]=w[u];
	int p1=str[u-SAM.fp].first,
		p2=str[u-SAM.fp].second;
	for (int i=0;i<=p2;i++)
		putchar(s[p1][i]+'a');

	for (int i=len-1;~i;i--)
		putchar(ans[i]+'a');
	putchar('\n');
	return ;
}

int main()
{
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&k);
	int Max=0;
	for (int i=0;i<n;i++)
	{
		m[i]=0;
		s[i].push_back(0);
		do {s[i][0]=getchar()-'a';}
			while (s[i][0]<0 || s[i][0]>25);
		do {s[i].push_back(getchar()-'a');++m[i];}
			while (s[i][m[i]]>=0 && s[i][m[i]]<26);
		Insert(s[i],m[i],i);
		if (m[Max]<m[i])
			Max=i;
	}
	if (m[Max]<k)
	{
		for (int i=0;i<m[Max];i++)
			putchar(s[Max][i]+'a');
		return 0;
	}
	BuildTree();
	Dfs(0);
	Solve();
	return 0;
}