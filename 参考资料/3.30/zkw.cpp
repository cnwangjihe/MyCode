bool SPFA()
{
    int head=0,tail=0,u,v;
    fill(dis,dis+MAXN,INF);
    memset(_in,0,sizeof _in);
    line[tail++]=T;
    dis[T]=0,_in[T]=1;
    while (head!=tail)
    {
        u=line[head++];
        for (int i=_head[u];~i;i=_next[i])
        {
            v=_node[i];
            if (_val[i^1] && dis[v]>dis[u]+_cost[i^1])
            {
                dis[v]=dis[u]+_cost[i^1];
                if (!_in[v])
                    _in[v]=1,line[tail++]=v;
            }
        }
        _in[u]=0;
    }
    return dis[S]!=INF;
}
int dfs(int u,int Min)
{
    _in[u]=1;
    if (u==T)
        return Min;
    int used=0,tmp,v;
    for(int i=_head[u];~i;i=_next[i])
    {
        v=_node[i];
        if(!_in[v] && _val[i] && dis[u]-_cost[i]==dis[v])
        {
            tmp=dfs(v,min(c[k],Min-ans));
            ans+=tmp*_cost[k];
            _val[i]-=tmp,_val[i^1]+=tmp,used+=tmp;
            if (used==Min)
                return used;
        }
    }
    return used;
}

int costflow()
{
    ans=0;
    while(SPFA())
    {
        do
        {
            memset(_in,0,sizeof _in);
            dfs(S,INF);
        }while (_in[T]);
    }
    return ans;
}
