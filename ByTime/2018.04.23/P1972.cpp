#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct Task{int l,r,i;};

const int MAXN = 500009,
          MAXM = 200000;

int cnt[MAXN],v[MAXN],p[MAXN],ans[MAXM];
Task q[MAXM];
int n,m,sum,col=0;

bool _cmp(int a,int b) {return v[a]<v[b];}
bool _cmpl(Task a,Task b){return a.l<b.l;}
bool _cmpr(Task a,Task b){return (a.r==b.r)?a.l<b.l:a.r<b.r;}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&v[i]),p[i]=i;
    sort(p+1,p+n+1,_cmp);
    for (int i=1;i<=n;i++)
    {
        while (i+1<=n && v[p[i]]==v[p[i+1]])
            v[p[i]]=col,i++;
        v[p[i]]=col++;
    }
    scanf("%d",&m);
    for (int i=0;i<m;i++)
        scanf("%d%d",&q[i].l,&q[i].r),q[i].i=i;
    sort(q,q+m,_cmpl);
    int d=sqrt(n),al=0,ar=al+d;
    for (int j=0;j<m;al+=d,ar+=d)
    {
    //	cerr << j << endl;
        int i=j;
        sum=0;
        while (j<m && q[j].l<=ar)
            j++;
    //	cerr << i << ' ' << j << endl;
        sort(q+i,q+j,_cmpr);
        memset(cnt,0,sizeof cnt);
        for (int x=q[i].l;x<=q[i].r;cnt[v[x]]++,x++)
            if (!cnt[v[x]])
                sum++;
        ans[q[i].i]=sum;
        for (int k=i+1;k<j;k++)
        {
            for (int x=q[k-1].r+1;x<=q[k].r;x++)
                if (!cnt[v[x]]++)
                    sum++;
            if (q[k].l<=q[k-1].l)
            {
                for (int x=q[k].l;x<q[k-1].l;x++)
                    if (!cnt[v[x]]++)
                        sum++;
            }
            else
            {
                for (int x=q[k-1].l;x<q[k].l;x++)
                    if (!--cnt[v[x]])
                        sum--;
            }
            ans[q[k].i]=sum;
        }
    }
    for (int i=0;i<m;i++)
        printf("%d\n",ans[i]);
    return 0;
}