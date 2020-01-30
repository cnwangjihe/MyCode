struct LCT
{
	inline bool Child(int u){return C[u][1]==u;}
	inline bool Isroot(int u){return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	inline void Up(int u){}
	inline void Down(int u)
	{
		if (!Rev[u])
			return ;
		if (C[u][0])
			Rev[C[u][0]]^=1;
		if (C[u][1])
			Rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		Rev[u]=0;
		return ;
	}
	inline void PushDown(int u)
	{
		if (!Isroot(u))
			PushDown(fa[u]);
		Down(u);
		return ;
	}
	void Rotate(int u)
	{
		int v=fa[u],w=fa[v],t=Child(u);
		if (!Isroot(v))
			C[w][Child(v)]=u;
		fa[u]=w;
		C[v][t]=C[u][t^1];
		fa[C[u][t^1]]=v;
		fa[v]=u;
		C[u][t^1]=v;
		Up(v);
		return ;
	}
	void Splay(int u)
	{
		PushDown(u);
		int v;
		while (!Isroot(u))
		{
			v=fa[u];
			if (!Isroot(v))
				Rotate(Child(v)==Child(u)?v:u);
			Rotate(u);
		}
		Up(u);
		return ;
	}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			C[u][1]=t;
			t=u,u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		Rev[u]^=1;
		return ;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		fa[u]=v;
		return ;
	}
	void Cut(int u,int v)
	{
		Makeroot(u);
		Access(v);
		Splay(v);
		C[v][0]=0;
		fa[u]=0;
	}
}

void ntt(int n,int *a,int type)
{
	for (int i=0,j=0;i<n;i++)
	{
		if (i>j)
			swap(a[i],a[j]);
		for (int l=(n>>1);(j^=l)<l;l>>=1);
	}
	int wn,x,y;
	for (int mid=1,midt=0;mid<n;mid<<=1,midt++)
	{
		wn=Wn[type==1][midt+1];
		for (int i=0;i<n;i+=(mid<<1))
			for (int j=i,w=1;j<i+mid;j++,w=Mul(w,wn))
			{
				x=a[j],y=Mul(a[j+mid],w);
				a[j]=Add(x,y),a[j+mid]=Add(x,Mod(-y));
			}
	}
	if (type==1)
		return ;
	int inv=qpow(n,MOD-2);
	for (int i=0;i<n;i++)
		a[i]=Mul(a[i],inv);
	return ;
}

void derivation(int n,int *a,int *b)
{
	for (int i=0;i<n-1;i++)
		b[i]=Mul(a[i+1],i+1);
	b[n-1]=0;
	return ;
}

void integral(int n,int *a,int *b)
{
	for (int i=n-1;i;i--)
		b[i]=Mul(qpow(i,MOD-2),a[i-1]);
	b[0]=0;
	return ;
}

void inverse(int n,int *a,int *b,int *t)
{
	if (n==1)
	{
		b[0]=qpow(a[0],MOD-2);
		return ;
	}
	int h=(n+1)>>1,len=1;
	while (len<(n<<1))
		len<<=1;
	inverse(h,a,b,t);
	fill(b+n,b+len,0);
	copy(a,a+n,t);
	fill(a+n,a+len,0);
	ntt(len,t,1);
	ntt(len,b,1);
	for (int i=0;i<len;i++)
		b[i]=Add(Mul(b[i],2),Mod(-Mul(t[i],Mul(b[i],b[i]))));
	ntt(len,b,-1);
}

void ln(int n,int *a,int *b,int *t)
{
	int len=1;
	while (len<(n<<1))
		len<<=1;
	inverse(n,a,b,t);
	derivation(n,a,t);
	fill(t,t+len,0);
	fill(b+n,b+len,0);
	ntt(len,b,1);
	ntt(len,t,1);
	for (int i=0;i<len;i++)
		b[i]=Mul(b[i],t[i]);
	ntt(len,b,-1);
	fill(b+n,b+len);
	return ;
}

struct Complex{int x,y,w;Complex(int t1=0,int t2=0,int t3=0):x(t1),y(t2),w(t3){}};

Complex Mul(const Complex &a,const Complex &b)
{return Complex(Add(Mul(a.x,b.x),Mul(a.w,Mul(a.y,b.y))),Add(Mul(a.x,b.y),Mul(a.y,b.x)),a.w);}

Complex qpow(Complex a,int k)
{
	Complex ans(1,0,a.w);
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if (k&(1<<i))
			ans=Mul(ans,a);
	return ans;
}

int modsqrt(int a)
{
	int w;
	do {b=rand();w=Add(Mul(b,b),Mod(-a));}
		while (qpow(w,(MOD-1)>>1)!=MOD-1);
	Complex ans=qpow(Complex(b,1,w),(MOD+1)>>1);
	return min(ans.x,Mod(-ans.x));
}

priority_queue Q;
void dij(int S)
{
	while (!Q.empty())
		Q.pop();
	fill(dis,dis+n+1,INF);
	memset(vis,0,sizeof vis);
	dis[S]=0;
	Q.push(mkp(dis[S],S));
	while (!Q.empty())
	{
		u=Q.top().second;
		if (vis[u])
			continue;
		vis[u]=1;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (dis[v]<=dis[u]+_val[i])
				continue;
			dis[v]=dis[u]+_val[i];
			Q.push(mkp(dis[v],v));
		}
	}
	return ;
}

namespace MaxFlow
{
	queue Q;
	bool bfs()
	{
		while (!Q.empty())
			Q.pop();
		fill(lev,lev+MAXN,INF);
		lev[S]=0;
		Q.push(S);
		while (!Q.empty())
		{
			u=Q.front(),Q.pop();
			for (int i=_head[u];~i;i=_next[i])
			{
				v=_node[i];
				if (lev[v]<=lev[u]+1 || !_val[i])
					continue;
				lev[v]=lev[u]+1;
				Q.push(v);
			}
		}
		return lev[T]!=INF;
	}
	int Dinic(int u,int sum)
	{
		if (u==T)
			return sum;
		int ans=0;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (!_val[i] || lev[u]+1!=lev[v])
				continue;
			w=Dinic(v,min(sum,_val[i]));
			_val[i]-=w,_val[i^1]+=w;
			sum-=w,ans+=w;
			if (!sum)
				break;
		}
		return ans;
	} 
}

void tarjan1(int u,int id)
{
	dfn[u]=++tim;
	S.push(u);
	_in[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (i==(id^1))
			continue;
		if (!dfn[v])
			tarjan1(v,i),low[u]=min(low[u],low[v]);
		else if (_in[v])
			low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]!=low[u])
		return ;
	m++;
	do {v=S.top(),S.pop(),col[v]=m;}
		while (v!=u);
	return ;
}

void tarjan2(int u)
{
	dfn[u]=++tim;
	S.push(u);
	_in[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (!dfn[v])
			tarjan1(v),low[u]=min(low[u],low[v]);
		else if (_in[v])
			low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]!=low[u])
		return ;
	m++;
	do {v=S.top(),S.pop(),col[v]=m;}
		while (v!=u);
	return ;
}

bool Gauss(int n,int *a)
{
	for (int i=0;i<n;i++)
	{
		id=i;
		for (int j=i+1;j<n;j++)
			if (abs(a[j][i])>abs(a[id][i]))
				id=j;
		if (id!=i)
			for (int j=0;j<=n;j++)
				swap(a[id][j],a[i][j]);
		if (abs(a[i][i])<eps)
			return 0;
		for (int j=0;j<n;j++)
		{
			if (j==i)
				continue;
			for (int k=n;k>=i;k--)
				a[j][k]-=a[j][i]/a[i][i]*a[i][k];
		}
	}
	for (int i=0;i<n;i++)
		a[i][i]=a[i][n]/a[i][i];
	return ;
}

queue<int> Q;

struct SAM
{
	int link[MAXN*2],len[MAXN*2],siz[MAXN*2];
	int nxt[MAXN*2][MAXC];
	int cnt[MAXN*2];
	int fp;
	SAM()
	{
		fp=1;
		memset(link,-1,sizeof link);
		memset(nxt,-1,sizeof nxt);
		memset(siz,0,sizeof siz);
	}
	void Extend(int c,int &last)
	{
		int u=fp++,p;
		len[u]=len[last]+1;
		siz[u]=1;
		for (p=last;~p && !~nxt[p][c];p=link[p])
			nxt[p][c]=u;
		if (!~p)
		{
			link[u]=0;
			last=u;
			return ;
		}
		int q=nxt[p][c];
		if (len[p]+1==len[q])
		{
			link[u]=q;
			last=u;
			return ;
		}
		int clone=fp++;
		copy(nxt[q]+0,nxt[q]+MAXC,nxt[clone]);
		link[clone]=link[q];
		len[clone]=len[p]+1;
		link[u]=clone,link[q]=clone;
		for (;~p && nxt[p][c]==q;p=link[p])
			nxt[p][c]=clone;
		last=u;
		return ;
	}
	long long Calc()
	{
		memset(cnt,0,sizeof cnt);
		while (!Q.empty())
			Q.pop();
		for (int i=1;i<fp;i++)
			cnt[link[i]]++;
		for (int i=1;i<fp;i++)
			if (!cnt[i])
				Q.push(i);
		long long ans=0;
		while (!Q.empty())
		{
			int u=Q.front();Q.pop();
			if (siz[u]!=1)
				ans=max(ans,1ll*len[u]*siz[u]);
			siz[link[u]]+=siz[u];
			if (!--cnt[link[u]])
				Q.push(link[u]);
		}
		return ans;
	}
}

namespace SA
{
	inline bool _cmp(int *rank,int i,int j,int len)
	{return rank[i]==rank[j] && rank[i+len]==rank[j+len];}
	
	void GetRank(int n,int m,int *rank,int *sa,int *tmp)
	{
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[i]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;~i;i--) sa[--cnt[rank[i]]]=i;
		for (int j=1,p=1;p!=n;j<<=1,m=p)
		{
			p=0;
			for (int i=n-j;i<n;i++) tmp[p++]=i;
			for (int i=0;i<n;i++) if (sa[i]>=j) tmp[p++]=sa[i]-j;
			for (int i=0;i<m;i++) cnt[i]=0;
			for (int i=0;i<n;i++) cnt[rank[tmp[i]]]++;
			for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
			for (int i=n-1;~i;i--) sa[--cnt[rank[tmp[i]]]]=tmp[i];
			for (int i=0;i<n;i++) swap(tmp[i],rank[i]);
			p=1,rank[sa[0]]=0;
			for (int i=1;i<n;i++)
				rank[sa[i]]=_cmp(tmp,sa[i],sa[i-1],j)?p-1:p++;
		}
		return ;
	}
	
	void GetHeight(int n,int m,int *rank,int *sa,int *s,int *h)
	{
		int x=0,j;
		for (int i=0;i<n;i++)
		{
			x-=(x>0);
			if (!rank[i])
				continue;
			j=sa[rank[i]-1];
			while (s[i+x]==s[j+x])
				x++;
			h[rank[i]]=x;
		}
		return ;
	}
}

