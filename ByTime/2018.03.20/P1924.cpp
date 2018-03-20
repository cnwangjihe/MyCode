#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 159,
          MAXM = (1<<11)+9;

int f[2][MAXM][MAXM];
int n,m,ans;
int a[MAXN];

__attribute__((optimize("-Os"))) inline void dfs(int a,int b,int c,int num,int k,int li)
{
    if (f[k][a][b]>num)
        return ;
    if (ans<num)
        ans=num;
    f[k][a][b]=num;
    int t=a&b&c;
    t=t&(t>>1)&li;
    while (t)
    {
        int tmp = t&-t;
        t ^= tmp;
        int p = tmp|(tmp<<1);
        dfs(a^p,b^p,c^p,num+1,k,~(tmp-1));
    }
    t=a&b&li;
    t=t&(t>>1)&(t>>2);
    while (t)
    {
        int tmp=t&-t;
        t^=tmp;
        int p=tmp|(tmp<<1)|(tmp<<2);
        dfs(a^p,b^p,c,num+1,k,~(tmp-1));
    }
    return ;
}

int main()
{
    int v;
    memset(a,0,sizeof a);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) 
        for (int j=0;j<m;j++)
        {
            scanf("%d",&v);
            a[i] |= ((v^1)<<j);
        }
    for (int i=2;i<=n;i++)
        for (int j=a[i-1];;j=(j-1)&a[i-1])
        {
            for (int k=a[i-2];;k=(k-1)&a[i-2])
            {
                dfs(a[i],j,k,f[(i&1)^1][j][k],i&1,(1<<11)-1);
                if (!k)
                    break;
            }
            if (!j)
                break;
        }
    printf("%d\n",ans);
    return 0;
}
