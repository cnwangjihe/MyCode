// Date      : 2018-12-26 08:59:15
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 生成函数
// Notice    : None

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 309;

long long a[MAXN],b[MAXN],f[MAXN];
int n;

int main()
{
//    freopen("HDU1398.in","r",stdin);
//    freopen("HDU1398.out","w",stdout);
    memset(f,0,sizeof f);
    memset(b,0,sizeof b);
    f[0]=1;
    for (int i=1;i<=17;i++)
    {
        memset(a,0,sizeof a);
        for (int j=0;j<=300;j+=i*i)
            a[j]=1;
        for (int j=0;j<=300;j++)
        {
            b[j]=0;
            for (int k=0;k<=j;k++)
                b[j]+=a[k]*f[j-k];
        }
        for (int i=0;i<=300;i++)
            f[i]=b[i];
    }
    while (scanf("%d",&n)==1 && n)
        printf("%lld\n",f[n]);
    return 0;
}