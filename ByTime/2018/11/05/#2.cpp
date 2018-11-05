#include<bits/stdc++.h>
using namespace std;
long long A[100],P[100]; 
char s[100];
int sz,r,n;
void solve()
{
    for (int i=1;i<=sz;i++)
    {
        for (int j=62;j>=0;j--)
        {
            if ((A[i]>>j)&1)
            {
                if (!P[j]) {P[j]=A[i]; break;}
                else A[i]^=P[j];
            }
        }
    }
    for (int j=0;j<=62;j++) if (P[j]) r++;
}
int main()
{
    scanf("%d%d",&n,&sz);
    for(int i=1;i<=sz;++i)
    {
        scanf("%s",s);
        for(int j=0;j<n;++j)
        if(s[j]=='O')
        A[i]^=(1ll<<j);
    }
    solve();
    printf("%lld",(1ll<<r)%2008);
}