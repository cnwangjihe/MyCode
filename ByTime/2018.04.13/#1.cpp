# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm> 
# include <cmath>
# include <cstdlib>
# include <vector>

using namespace std;
const int maxN=3005;
struct data
{
	int hi,id,fa;
}x[maxN];
int n,f1[maxN],f2[maxN],f3[maxN],f4[maxN];
vector<int> path[maxN];

bool cmp1(data a,data b) { return a.hi<b.hi;}
bool cmp2(data a,data b) { return a.id<b.id;}

void dfs(int k)
{
	f4[x[k].hi]=max(f4[x[k].hi],1);
	for (int i=x[k].hi+1; i<=n; i++)
	  f4[x[k].hi]=max(f4[x[k].hi],f4[i]+1);
	for (int i=0; i<path[k].size(); i++)
	if (path[k][i]!=x[k].fa){
		dfs(path[k][i]);
	}
	f3[x[k].hi]=max(f3[x[k].hi],1);
	for (int i=1; i<x[k].hi; i++)
	  f3[x[k].hi]=max(f3[x[k].hi],f3[i]+1);
}

void get_high(int k,int up)
{
	x[k].fa=up;
	for (int i=0; i<path[k].size(); i++)
	if (path[k][i]!=up) get_high(path[k][i],k);
}

int main()
{
//	freopen("2444.in","r",stdin);
//	freopen("2444.out","w",stdout);
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	    scanf("%d",&x[i].hi),x[i].id;
	sort(x+1,x+1+n,cmp1);
	for (int i=1,last=-1; i<=n; i++)
	    if (x[i].hi!=last) last=x[i].hi,x[i].hi=x[i-1].hi+1;
	    else x[i].hi=x[i-1].hi;
	sort(x+1,x+1+n,cmp2);
	int u,v;
	for (int i=1; i<n; i++)
	{
	    scanf("%d%d",&u,&v);
	    path[u].push_back(v);
	    path[v].push_back(u);
	}
	get_high(1,0);
	int ans=0;
	for (int d=1; d<=n; d++)
	{
		memset(f1,0,sizeof f1); 
		memset(f2,0,sizeof f2);
	    for (int j=0; j<path[d].size(); j++)
		{
		    memset(f3,0,sizeof f3);
		    memset(f4,0,sizeof f4);
		    dfs(path[d][j]);
		    for (int i=n; i>=1; i--) f3[i]=max(f3[i],f3[i+1]);
		    for (int i=1; i<=n; i++) f4[i]=max(f4[i],f4[i-1]);
		    ans=max(ans,f1[x[d].hi-1]+1+f4[x[d].hi+1]);
		    ans=max(ans,f3[x[d].hi-1]+1+f2[x[d].hi+1]);
		    for (int i=1; i<=n; i++)
			{
			    ans=max(ans,f1[i-1]+f4[i]);
			    ans=max(ans,f3[i-1]+f2[i]);
			    f1[i]=max(f1[i],f3[i]);
			    f2[i]=max(f2[i],f4[i]);
			}
	    }
	}
	printf("%d\n",ans);
	return 0;
}