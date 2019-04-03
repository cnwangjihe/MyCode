#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int N=1e6+10,M=N<<1,inf=1e9;
int goal,con[M],cc[M];
stack<int>fans;

namespace String
{
	struct Trie
	{
		int rt,sz,ch[N][26],fa[N],lt[N];
		void init(){rt=sz=1;}
		void insert(char *s,int n)
		{
			int now=rt;
			for(int i=1;i<=n;++i)
			{
				int c=s[i]-'a';
				if(!ch[now][c]) ch[now][c]=++sz,fa[sz]=now,lt[sz]=c;
				now=ch[now][c];
			}
		}
	}T;
	struct SAM
	{
		int sz,las,fa[M],mx[M],ch[M][26],rem[M],pos[M];
		stack<int>stk;
		queue<int>que;
		void init(){sz=las=1;}
		int extend(int c,int lt)
		{
			las=lt;
			int p,q,np,nq;
			p=las;las=np=++sz;mx[np]=mx[p]+1;
			while(p && !ch[p][c]) ch[p][c]=np,p=fa[p];
			if(!p) fa[np]=1;
			else
			{
				q=ch[p][c];
				if(mx[p]+1==mx[q]) fa[np]=q;
				else
				{
					nq=++sz;mx[nq]=mx[p]+1;
					memcpy(ch[nq],ch[q],sizeof(ch[q]));
					fa[nq]=fa[q];fa[np]=fa[q]=nq;
					while(p && ch[p][c]==q) ch[p][c]=nq,p=fa[p];
				}
			}
			return las;
		}
		void dfs(int x)
	    {
	        if(!goal) return;
	        if(x==rem[goal])
	        {
	            goal=0;
	            while(!stk.empty()) fans.push(stk.top()),stk.pop();
	            return;
	        }
	        for(int i=0;i<26;++i) if(T.ch[x][i])
	        {
	            stk.push(i),dfs(T.ch[x][i]);
	            if(stk.size()) stk.pop();
	        }
	    }
	    void buildsam()
	    {
	    	init();
	    	for(int i=0;i<26;++i) if(T.ch[T.rt][i]) que.push(T.ch[T.rt][i]);
	    	pos[T.rt]=1;rem[pos[T.rt]]=T.rt;
	    	while(!que.empty())
	    	{
	    		int x=que.front();que.pop();
	    		//printf("%d %d %d\n",x,T.lt[x],pos[T.fa[x]]);
	    		pos[x]=extend(T.lt[x],pos[T.fa[x]]);rem[pos[x]]=x;
	    		for(int i=0;i<26;++i) if(T.ch[x][i]) que.push(T.ch[x][i]);
	    	}
	    	//for(int i=1;i<=T.sz;++i) printf("%d %d %d\n",i,pos[i],rem[pos[i]]);
	    }
	}S;
}
using namespace String;

namespace DreamLolita
{
	int ans,tot,n,m,K;
	int head[M],vis[M],f[M];
	char s[N],rs[N];
	stack<int>quick[26];
	vector<int>G[M];
	struct Tway{int v,nex;}e[M<<1];
	void add(int u,int v){e[++tot]=(Tway){v,head[u]};head[u]=tot;}
	void dfs(int x)
	{
		if(S.mx[x]>=K)
		{
			for(int c=0;c<26;++c) 
			{
				if(S.ch[x][c]) {if(S.mx[S.ch[x][c]]>=K) add(S.ch[x][c],x);}
				else if(quick[c].size()) add(quick[c].top(),x);
			}
		}
		if(S.mx[x]+1>=K){for(int c=0;c<26;++c) if(S.ch[x][c]) quick[c].push(S.ch[x][c]);}
		for(int i=0;i<(int)G[x].size();++i) dfs(G[x][i]);
		if(S.mx[x]+1>=K){for(int c=0;c<26;++c) if(S.ch[x][c]) quick[c].pop();}
	}
	void buildmap()
	{
		for(int i=1;i<=S.sz;++i) for(int c=0;c<26;++c) cc[S.ch[i][c]]=c;
		for(int i=2;i<=S.sz;++i) G[S.fa[i]].pb(i);
		dfs(1);
		/*for(int i=1;i<=S.sz;++i) if(S.mx[i]>=K)
		{
			for(int c=0;c<26;++c) 
			{
				if(S.ch[i][c]){if(S.mx[S.ch[i][c]]>=K) add(S.ch[i][c],i);}
				else
				{
					int p=i;
					for(;p && !S.ch[p][c] && S.mx[p]>=K;p=S.fa[p]);
					int np=S.ch[p][c];
					if(p && np && S.mx[p]+1>=K) add(np,i);
				}
			}
		}*/
	}
	int dfsway(int x)
	{
		if(vis[x]) return (f[x]=inf);
		if(~f[x]) return f[x];
		f[x]=S.mx[x];vis[x]=1;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v,res=dfsway(v);
			if(res==inf) return (f[x]=inf);
			if(res+1>f[x]) con[x]=v,f[x]=res+1;
		}
		vis[x]=0;return f[x];
	}
	void getans()
	{
		memset(f,-1,sizeof(f));
		for(int i=1;i<=S.sz;++i) if(S.mx[i]>=K && !~f[i]) dfsway(i);
		for(int i=1;i<=S.sz;++i) ans=max(ans,f[i]);
		if(ans>=inf) {puts("INF");exit(0);}
		for(int i=1;i<=S.sz;++i) if(ans==f[i])
		{
			int j=i;
			while(con[j]) fans.push(cc[j]),j=con[j];
			goal=j;S.dfs(1);//printf("goal:%d %d\n",goal,S.rem[goal]);
			break;
		}
		while(fans.size()) putchar(fans.top()+'a'),fans.pop();
	}
	void solution()
	{
		scanf("%d%d",&m,&K);T.init();
		if(m==2 && K==1) {puts("INF");return;}
		int mx=0,tmp=0;
		for(int i=1;i<=m;++i)
		{
			scanf("%s",s+1);tmp=strlen(s+1);T.insert(s,tmp);
			if(tmp>mx) {mx=tmp;for(int j=1;j<=mx;++j)rs[j]=s[j];}
		}
		if(mx<K){for(int i=1;i<=mx;++i)putchar(rs[i]);return;}
		S.buildsam();buildmap();getans();
	}
}

int main()
{
	freopen("2815.in","r",stdin);
	freopen("2815.out","w",stdout);
	DreamLolita::solution();
	return 0;
}