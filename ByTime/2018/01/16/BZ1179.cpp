#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stack>
#include <queue>
using namespace std; 
#define M 500005 
int in() { int t=0;char ch=getchar(); while (!isdigit(ch)) ch=getchar(); while (isdigit(ch)) t=(t<<1)+(t<<3)+ch-48,ch=getchar(); return t; } int n=in(),m=in(),s,p,tot,cnt; struct edge{int u,v,next;}e[M],E[M]; int first[M],c[M],dfn[M],low[M],belong[M],First[M],C[M],dis[M]; bool is_end[M],vis[M]; stack<int>S; queue<int>Q; void add(int y,int x){e[++tot]=(edge){x,y,first[x]};first[x]=tot;} void Add(int x,int y){E[++tot]=(edge){x,y,First[x]};First[x]=tot;} void dfs(int x) { dfn[x]=low[x]=++cnt; S.push(x); vis[x]=1; for (int i=first[x];i;i=e[i].next) if (!dfn[e[i].v]) dfs(e[i].v), low[x]=min(low[x],low[e[i].v]); else if (vis[e[i].v]) low[x]=min(low[x],dfn[e[i].v]); if (dfn[x]==low[x]) { C[x]=0; for (int y=-1;y!=x;y=S.top(),S.pop()) belong[S.top()]=x, C[x]+=c[S.top()], vis[S.top()]=0; } } main() { for (int i=1;i<=m;i++) add(in(),in()); for (int i=1;i<=n;i++) c[i]=in(); s=in();p=in(); for (int i=1;i<=p;i++) is_end[in()]=1; tot=0; for (int i=1;i<=n;i++) if (!dfn[i]) dfs(i); for (int i=1;i<=n;i++) for (int j=first[i];j;j=e[j].next) if (belong[i]!=belong[e[j].v]) Add(belong[i],belong[e[j].v]); memset(dis,63,sizeof(dis)); Q.push(belong[s]);vis[belong[s]]=1; dis[belong[s]]=-C[belong[s]]; while (!Q.empty()) { int x=Q.front(); Q.pop(); vis[x]=0; for (int i=First[x];i;i=E[i].next) if (dis[x]-C[E[i].v]<dis[E[i].v]) { dis[E[i].v]=dis[x]-C[E[i].v]; if (!vis[E[i].v]) Q.push(E[i].v),vis[E[i].v]=1; } } int ans=0; for (int i=1;i<=n;i++) if (is_end[i]) ans=min(ans,dis[belong[i]]); printf("%d",-ans); }
