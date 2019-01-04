#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<queue>
#define ll long long
const int MAXN=2e5+10;
int sa[MAXN],rank[MAXN],rsort[MAXN],y[MAXN],wr[MAXN],height[MAXN];
char a[MAXN];
bool cmp(int a,int b,int len)
{
    return wr[a]==wr[b] && wr[a+len]==wr[b+len];
}
void get_SA(int m,int n)
{
    for(int i=1;i<=n;i++) rank[i]=a[i-1];
    for(int i=1;i<=n;i++) rsort[rank[i]]++;
    for(int i=1;i<=m;i++) rsort[i]+=rsort[i-1];
    for(int i=n;i>0;i--) sa[rsort[rank[i]]--]=i;
    int len=1,p=0;
    while(p<n)
    {
        int k=0;
        //y[i]:以第二关键字排名,排名为i的第一关键字的位置
        for(int i=n-len+1;i<=n;i++) y[++k]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) y[++k]=sa[i]-len;
        for(int i=1;i<=n;i++) wr[i]=rank[y[i]];
        //wr[i]:以第二关键字排序,排名为i的第一关键字的排名
        memset(rsort,0,sizeof(rsort));
        for(int i=1;i<=n;i++) rsort[wr[i]]++;
        for(int i=1;i<=m;i++) rsort[i]+=rsort[i-1];
        for(int i=n;i>0;i--) sa[rsort[wr[i]]--]=y[i];
        for(int i=1;i<=n;i++) wr[i]=rank[i];
        p=1;rank[sa[1]]=1;
        for(int i=2;i<=n;i++)
        {
            if(!cmp(sa[i],sa[i-1],len)) p++;
            rank[sa[i]]=p;
        }
        m=p;len<<=1;
    }
}
//线性求解height数组
void get_height(int n)
{
    int k=0,j;
    for(int i=1;i<=n;i++)
    {
        j=sa[rank[i]-1];
        if(k) k--;
        while(a[j+k-1]==a[i+k-1]) k++;
        height[rank[i]]=k;
    }
}
ll solve(int n)
{
    ll ans=0;
    for(int i=1;i<=n;i++)
        ans+=n+1-sa[i]-height[i];
    return ans;
}
int main()
{
    int len;
    scanf("%d",&len);
    scanf("%s",a);
    get_SA(300,len);
    get_height(len);
    for (int i=0;i<len;i++)
        printf("%d %d\n",rank[i],height[i]);
    printf("%lld",solve(len));
    return 0;
}