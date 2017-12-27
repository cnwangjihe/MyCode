struct SplayTree
{
	int v,w,y,v1,w1,y1;
	Splay()
	{
		fp=0;
		Val[0]=Min[0]=INF;
		Add[0]=Rev[0]=0;
		Siz[0]=0;
		fa[0]=0;
	}
	inline bool Ch(int u,int v) { return c[v][1]==u; }
	int Create(int v)
	{
		Siz[++fp]=1;
		Min[fp]=Val[fp]=v;
		Rev[fp]=Add[fp]=0;
		return fp;
	}
	void Up(int u)
	{
		if (!u) return ;
		Min[u]=min(min(Min[c[u][0]],Min[c[u][1]]),Val[u]);
		Siz[u]=Siz[c[u][0]]+Siz[c[u][1]]+1;
	}
	void Down(int u)
	{
		if (c[u][0])
			Val[c[u][0]]+=Add[u],
			Min[c[u][0]]+=Add[u],
			Add[c[u][0]]+=Add[u],
			Rev[c[u][0]]^=Rev[u];
		if (c[u][1])
			Val[c[u][1]]+=Add[u],
			Min[c[u][1]]+=Add[u],
			Add[c[u][1]]+=Add[u],
			Rev[c[u][1]]^=Rev[u];
	}
	void Push(int u)
	{
		if (fa[u]) Push(fa[u]);
		Down(u);
	}
	void Rotato(int u)
	{
		v=fa[u], w=fa[v], y=c[u][Ch(u,v)^1];
		c[v][Ch(u,v)]=y; fa[y]=v;
		c[u][Ch(u,v)^1]=v; fa[v]=u;
		c[w][Ch(v,w)]=u; fa[u]=w;
		if (!w) root=u;
		Up(v);Up(u);
	}
	void Splay(int u,int tar)
	{
		Push(u);
		for (;fa[u]!=tar;Rotato(u))
		{
			v1=fa[u],w1=fa[v1];
			if (Ch(u,v1)==Ch(v1,w1)) Rotato(v1);
				else Rotato(u);
		}
		Up(u);
	}
	void Insert(int v)
	{
		
	}
};
