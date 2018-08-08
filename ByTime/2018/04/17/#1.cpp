#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define inf 1000000000
using namespace std;
LL read()
{
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
int n,m,cnt;
int a[100005],l[1000005],r[1000005];
void solve(int t)
{
    if(t==m)return;
    vector<int>q;
    for(int i=1;i<=n;i++)
        if((a[i]/t)&1)q.push_back(i);
    for(int i=0;i<q.size();i+=2)
    {
    	if(a[q[i]]>a[q[i+1]])swap(q[i],q[i+1]);
        a[q[i+1]]-=a[q[i]];
        a[q[i]]*=2;
        l[++cnt]=q[i];r[cnt]=q[i+1];
    }
    solve(t*2);
}
int main()
{
    freopen("candy.in","r",stdin);
	freopen("#1.out","w",stdout);
    int T=read();
    while(T--)
    {
        n=read();m=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        int t=0;
        for(int i=1;i<=n;i++)
            t=gcd(t,a[i]);
        int x=m/t;
        while(x%2==0)x/=2;
        if(x!=1)
        {
            puts("no");
            puts("0");
        }
        else
        {
            puts("yes");
            puts("0");
        }
    }
    return 0;
}

